// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../impl/MeasureReader.h"
#include "../api/ClefData.h"
#include "../api/KeyData.h"
#include "../api/NoteData.h"
#include "../api/Smufl.h"
#include "../core/elements/Alter.h"
#include "../core/elements/Backup.h"
#include "../core/elements/Barline.h"
#include "../core/elements/Beats.h"
#include "../core/elements/BeatType.h"
#include "../core/elements/Bookmark.h"
#include "../core/elements/Cancel.h"
#include "../core/elements/Cancel.h"
#include "../core/elements/Clef.h"
#include "../core/elements/ClefOctaveChange.h"
#include "../core/elements/CueNoteGroup.h"
#include "../core/elements/Direction.h"
#include "../core/elements/DisplayOctave.h"
#include "../core/elements/DisplayStep.h"
#include "../core/elements/DisplayStepOctaveGroup.h"
#include "../core/elements/Duration.h"
#include "../core/elements/EditorialVoiceGroup.h"
#include "../core/elements/Fifths.h"
#include "../core/elements/Fifths.h"
#include "../core/elements/FiguredBass.h"
#include "../core/elements/Forward.h"
#include "../core/elements/FullNoteGroup.h"
#include "../core/elements/FullNoteTypeChoice.h"
#include "../core/elements/GraceNoteGroup.h"
#include "../core/elements/Grouping.h"
#include "../core/elements/Harmony.h"
#include "../core/elements/Key.h"
#include "../core/elements/KeyAccidental.h"
#include "../core/elements/KeyAlter.h"
#include "../core/elements/KeyChoice.h"
#include "../core/elements/KeyOctave.h"
#include "../core/elements/KeyStep.h"
#include "../core/elements/Line.h"
#include "../core/elements/Link.h"
#include "../core/elements/MeasureStyle.h"
#include "../core/elements/MeasureStyleChoice.h"
#include "../core/elements/Mode.h"
#include "../core/elements/Mode.h"
#include "../core/elements/MultipleRest.h"
#include "../core/elements/MusicDataChoice.h"
#include "../core/elements/MusicDataGroup.h"
#include "../core/elements/NonTraditionalKey.h"
#include "../core/elements/NormalNoteGroup.h"
#include "../core/elements/Note.h"
#include "../core/elements/NoteChoice.h"
#include "../core/elements/Octave.h"
#include "../core/elements/Pitch.h"
#include "../core/elements/Print.h"
#include "../core/elements/Properties.h"
#include "../core/elements/Properties.h"
#include "../core/elements/Rest.h"
#include "../core/elements/Sign.h"
#include "../core/elements/Sound.h"
#include "../core/elements/Staff.h"
#include "../core/elements/Step.h"
#include "../core/elements/Time.h"
#include "../core/elements/TimeChoice.h"
#include "../core/elements/TimeSignatureGroup.h"
#include "../core/elements/TraditionalKey.h"
#include "../core/elements/Type.h"
#include "../core/elements/Unpitched.h"
#include "../core/elements/BarStyle.h"
#include "../core/elements/Voice.h"
#include "../impl/Converter.h"
#include "../impl/DirectionReader.h"
#include "../impl/NoteFunctions.h"
#include "../impl/NoteReader.h"
#include "../impl/TimeReader.h"
#include "../utility/Throw.h"

#include <set>

namespace mx
{
    namespace impl
    {
        MeasureReader::MeasureReader( const core::PartwiseMeasure& inPartwiseMeasureRef, const MeasureCursor& cursor, const MeasureCursor& previousMeasureCursor )
        : myMutex{}
        , myPartwiseMeasure{ inPartwiseMeasureRef }
        , myConverter{}
        , myOutMeasureData{}
        , myCurrentCursor{ cursor }
        , myPreviousCursor{ previousMeasureCursor }
        {
            
        }
        
        void MeasureReader::addStavesToOutMeasure() const
        {
            for( int i = 0; i < myCurrentCursor.getNumStaves(); ++i )
            {
                myOutMeasureData.staves.emplace_back( api::StaffData{} );
            }
        }

        api::MeasureData MeasureReader::getMeasureData() const
        {
            // lock due to the use of a mutable in const function
            // TODO - that's stupid, remove const designations
            std::lock_guard<std::mutex> lock(myMutex);
            myOutMeasureData = api::MeasureData{};
            const auto& attr = *myPartwiseMeasure.getAttributes();
            myOutMeasureData.number = attr.number.getValue();
            
            if( myOutMeasureData.number == std::to_string( myCurrentCursor.measureIndex + 1 ) )
            {
                myOutMeasureData.number = "";
            }
            
            if( attr.hasWidth )
            {
                myOutMeasureData.width = attr.width.getValue();
            }
            
            if( attr.hasImplicit )
            {
                myOutMeasureData.implicit = attr.implicit == core::YesNo::yes ? api::Bool::yes : api::Bool::no;
            }
            
            addStavesToOutMeasure();
            parseTimeSignature();
            
            const auto& mdcSet = myPartwiseMeasure.getMusicDataGroup()->getMusicDataChoiceSet();
            auto iter = mdcSet.cbegin();
            const auto endIter = mdcSet.cend();
            
            for( ; iter != endIter; ++iter )
            {
                const auto& mdc = **iter;
                
                // incredibly, we need to know if the note following this one has a 'chord' tag
                // otherwise we don't know whether or not the current note if part of a chord,
                // which we need to know so that we can choose whether or not to increment the
                // current tick position in myCurrentCursor
                auto peekAheadAtNextNoteIter = iter + 1;
                
                while( mdc.getChoice() == core::MusicDataChoice::Choice::note
                       && peekAheadAtNextNoteIter != endIter
                       && (*peekAheadAtNextNoteIter)->getChoice() != core::MusicDataChoice::Choice::note )
                {
                    ++peekAheadAtNextNoteIter;
                }
                
                core::NotePtr nextNotePtr = nullptr;
                if( peekAheadAtNextNoteIter != endIter )
                {
                    nextNotePtr = (*peekAheadAtNextNoteIter)->getNote();
                }
                
                parseMusicDataChoice( mdc, nextNotePtr );
            }
            
            myCurrentCursor.isFirstMeasureInPart = false;
            
            consolidateVoicesForAllStaves();
            
            // move the data to a temp then return the temp
            auto temp = api::MeasureData{ std::move(myOutMeasureData) };
            myOutMeasureData = api::MeasureData{};
            return temp;
        }
        
        
        void MeasureReader::parseTimeSignature() const
        {
            TimeReader timeReader{ myPartwiseMeasure.getMusicDataGroup()->getMusicDataChoiceSet() };
            api::TimeSignatureData timeSignature;
            
            if( timeReader.getIsTimeFound() )
            {
                timeSignature = timeReader.getTimeSignatureData();
                timeSignature.isImplicit = false;
            }
            else // no time signature was found
            {
                if( myCurrentCursor.measureIndex > 0 )
                {
                    timeSignature = myPreviousCursor.timeSignature;
                }
                timeSignature.isImplicit = true;
            }

            myOutMeasureData.timeSignature = timeSignature;
            myCurrentCursor.timeSignature = timeSignature;
        }
        
        
        void MeasureReader::parseMusicDataChoice( const core::MusicDataChoice& mdc, const core::NotePtr& nextNotePtr ) const
        {
            switch ( mdc.getChoice() )
            {
                case core::MusicDataChoice::Choice::note:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseNote( *mdc.getNote(), nextNotePtr );
                    break;
                }
                case core::MusicDataChoice::Choice::backup:
                {
                    parseBackup( *mdc.getBackup() );
                    
                    if( myCurrentCursor.tickTimePosition < 0 )
                    {
                        myCurrentCursor.tickTimePosition = 0;
                        // TODO - log or inform the client that the file is erroneous
                    }
                    break;
                }
                case core::MusicDataChoice::Choice::forward:
                {
                    
                    myCurrentCursor.isBackupInProgress = false;
                    parseForward( *mdc.getForward() );
                    break;
                }
                case core::MusicDataChoice::Choice::direction:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseDirection( *mdc.getDirection() );
                    break;
                }
                case core::MusicDataChoice::Choice::properties:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseProperties( *mdc.getProperties() );
                    break;
                }
                case core::MusicDataChoice::Choice::harmony:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseHarmony( *mdc.getHarmony() );
                    break;
                }
                case core::MusicDataChoice::Choice::figuredBass:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseFiguredBass( *mdc.getFiguredBass() );
                    break;
                }
                case core::MusicDataChoice::Choice::print:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parsePrint( *mdc.getPrint() );
                    break;
                }
                case core::MusicDataChoice::Choice::sound:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseSound( *mdc.getSound() );
                    break;
                }
                case core::MusicDataChoice::Choice::barline:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseBarline( *mdc.getBarline() );
                    break;
                }
                case core::MusicDataChoice::Choice::grouping:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseGrouping( *mdc.getGrouping() );
                    break;
                }
                case core::MusicDataChoice::Choice::link:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseLink( *mdc.getLink() );
                    break;
                }
                case core::MusicDataChoice::Choice::bookmark:
                {
                    myCurrentCursor.isBackupInProgress = false;
                    parseBookmark( *mdc.getBookmark() );
                    break;
                }
                default:
                {
                    MX_THROW( "unsupported MusicDataChoice::Choice value" );
                }
            }
        }
        
        
        void MeasureReader::parseNote( const core::Note& inMxNote, const core::NotePtr& nextNotePtr ) const
        {
            MX_UNUSED( inMxNote );
            MX_UNUSED( nextNotePtr );
            
            bool isNextNotePartOfAChord = false;
            
            if( nextNotePtr )
            {
                NoteReader nextNoteReader{ *nextNotePtr };
                isNextNotePartOfAChord = nextNoteReader.getIsChord();
            }
            
            myCurrentCursor.isBackupInProgress = false;
            impl::NoteReader noteReader{ inMxNote };
            impl::NoteFunctions noteFunc{ inMxNote, myCurrentCursor};
            auto noteData = noteFunc.parseNote();
            
            int noteDataStaffIndex = noteReader.getStaffNumber() - 1;
            
            if( noteDataStaffIndex < 0 )
            {
                noteDataStaffIndex = 0;
            }
            
            myCurrentCursor.staffIndex = noteDataStaffIndex;
            
            bool isThisNotePartOfAChord = noteData.isChord || isNextNotePartOfAChord;
            noteData.isChord = isThisNotePartOfAChord;
            
            if( !isThisNotePartOfAChord || !isNextNotePartOfAChord )
            {
                myCurrentCursor.tickTimePosition += noteData.durationData.durationTimeTicks;
            }
            
            MX_ASSERT( noteDataStaffIndex >= 0 );
            MX_ASSERT( static_cast<size_t>( noteDataStaffIndex ) < myOutMeasureData.staves.size() );
            insertNoteData( std::move(noteData), myCurrentCursor.staffIndex, myCurrentCursor.voiceIndex );
        }
        
        
        void MeasureReader::parseBackup( const core::Backup& inMxBackup ) const
        {
            if( ! ( myCurrentCursor.isBackupInProgress ) )
            {
                ++myCurrentCursor.voiceIndex;
            }
            else
            {
                // TODO - remove this debugging check
                MX_THROW( "multiple backups in a row" );
            }
            myCurrentCursor.isBackupInProgress = true;
            const int backupAmount = myCurrentCursor.convertDurationToGlobalTickScale( *inMxBackup.getDuration() );
            myCurrentCursor.tickTimePosition -= backupAmount;
        }
        
        
        void MeasureReader::parseForward( const core::Forward& inMxForward ) const
        {
            const int forwardAmount = myCurrentCursor.convertDurationToGlobalTickScale( *inMxForward.getDuration() );
            myCurrentCursor.tickTimePosition += forwardAmount;
        }
        
        
        void MeasureReader::parseDirection( const core::Direction& inMxDirection ) const
        {
            DirectionReader reader{ inMxDirection, myCurrentCursor };
            auto directionData = reader.getDirectionData();
            
            // make an adjustment if the directionData refers to a non-existant staff
            size_t staffIndex = 0;
            bool isStaffIndexSpecified = inMxDirection.getHasStaff();
            bool isStaffIndexInsane = false;

            if( isStaffIndexSpecified )
            {
                staffIndex = static_cast<size_t>( inMxDirection.getStaff()->getValue().getValue() - 1 );
            }
            
            isStaffIndexInsane = staffIndex >= myOutMeasureData.staves.size();
            
            if( !isStaffIndexSpecified || isStaffIndexInsane )
            {
                staffIndex = 0;
                directionData.isStaffValueSpecified = false;
            }
            else
            {
                directionData.isStaffValueSpecified = true;
            }
            
            // in-case we made a mistake in the code above which calculates the staffIndex
            // make a final check to see if the staffIndex is in-bounds - throw if stupid
            MX_ASSERT( staffIndex < myOutMeasureData.staves.size() );
            auto& staff = myOutMeasureData.staves.at( staffIndex );
            staff.directions.emplace_back( std::move( directionData ) );
        }
        
        
        void MeasureReader::parseProperties( const core::Properties& inMxProperties ) const
        {
            // TODO - continue work on measure numbering and style etc
            for( const auto& measureStylePtr : inMxProperties.getMeasureStyleSet() )
            {
                const auto& measureStyle = *measureStylePtr;
                if( measureStyle.getMeasureStyleChoice()->getChoice() == core::MeasureStyleChoice::Choice::multipleRest )
                {
                    const auto& mr = *measureStyle.getMeasureStyleChoice()->getMultipleRest();
                    if( !mr.getValue().getIsEmpty() )
                    {
                        const auto value = mr.getValue().getValueNumber().getValue();
                        myOutMeasureData.multiMeasureRest = value;
                    }
                }
            }
            
            for( const auto& keyPtr : inMxProperties.getKeySet() )
            {
                
                const auto& key = *keyPtr;
                const auto& attr = *key.getAttributes();
                const auto keyChoiceObj = *key.getKeyChoice();
                const auto keyType = keyChoiceObj.getChoice();

                if( keyType == core::KeyChoice::Choice::nonTraditionalKey )
                {
                    // TODO - support non-traditional keys
                    continue;
                }
                
                api::KeyData keyData;
                // TODO - do position attributes
                const auto& traditionalKey = *keyChoiceObj.getTraditionalKey();
                
                if( attr.hasNumber )
                {
                    keyData.staffIndex = attr.number.getValue() - 1;
                    if( keyData.staffIndex > myCurrentCursor.getNumStaves() - 1 )
                    {
                        keyData.staffIndex = -1;
                    }
                }
                
                keyData.fifths = traditionalKey.getFifths()->getValue().getValue();
                if( traditionalKey.getHasCancel() )
                {
                    keyData.cancel = traditionalKey.getCancel()->getValue().getValue();
                }
                
                if( traditionalKey.getHasMode() )
                {
                    // TODO - support all modes, not just major/minor
                    const auto coreMode = traditionalKey.getMode()->getValue().getValue();
                    if( coreMode == core::ModeEnum::major )
                    {
                        keyData.mode = api::KeyMode::major;
                    }
                    else if( coreMode == core::ModeEnum::minor )
                    {
                        keyData.mode = api::KeyMode::minor;
                    }
                    else if( coreMode == core::ModeEnum::minor )
                    {
                        keyData.mode = api::KeyMode::unsupported;
                    }
                }
                keyData.tickTimePosition = myCurrentCursor.tickTimePosition;
                
                myOutMeasureData.keys.emplace_back( std::move( keyData ) );
            }
            importClefs( inMxProperties.getClefSet() );
        }
        
        
        void MeasureReader::parseHarmony( const core::Harmony& inMxHarmony ) const
        {
            coutItemNotSupported( inMxHarmony );
        }
        
        
        void MeasureReader::parseFiguredBass( const core::FiguredBass& inMxFiguredBass ) const
        {
            coutItemNotSupported( inMxFiguredBass );
        }
        
        
        void MeasureReader::parsePrint( const core::Print& inMxPrint ) const
        {
            coutItemNotSupported( inMxPrint );
        }
        
        
        void MeasureReader::parseSound( const core::Sound& inMxSound ) const
        {
            coutItemNotSupported( inMxSound );
        }
        
        
        void MeasureReader::parseBarline( const core::Barline& inMxBarline ) const
        {
            auto barline = api::BarlineData{};
            const auto& attr = *inMxBarline.getAttributes();
            auto loc = api::HorizontalAlignment::unspecified;
            auto style = api::BarlineType::unspecified;
            
            if( attr.hasLocation )
            {
                loc = myConverter.convertBarlinePlacement( attr.location );
            }
            
            if( inMxBarline.getHasBarStyle() )
            {
                style = myConverter.convert( inMxBarline.getBarStyle()->getValue() );
            }
            
            // make a right-side barline last in the data
            if( loc == api::HorizontalAlignment::right )
            {
                barline.tickTimePosition = api::TICK_TIME_INFINITY;
            }
            else
            {
                barline.tickTimePosition = myCurrentCursor.tickTimePosition;
            }
            
            barline.barlineType = style;
            barline.location = loc;
            myOutMeasureData.barlines.emplace_back( std::move( barline ) );
        }
        
        
        void MeasureReader::parseGrouping( const core::Grouping& inMxGrouping ) const
        {
            coutItemNotSupported( inMxGrouping );
        }
        
        
        void MeasureReader::parseLink( const core::Link& inMxLink ) const
        {
            coutItemNotSupported( inMxLink );
        }
        
        
        void MeasureReader::parseBookmark( const core::Bookmark& inMxBookmark ) const
        {
            coutItemNotSupported( inMxBookmark );
        }
        
        
        void MeasureReader::coutItemNotSupported( const core::ElementInterface& element ) const
        {
            MX_UNUSED(element);
            //std::cout << element.getElementName() << " is not supported" << std::endl;
        }
        
        
        void MeasureReader::importClefs( const core::ClefSet& inClefs ) const
        {
            auto iter = inClefs.cbegin();
            auto endIter = inClefs.cend();
            
            for( ; iter != endIter; ++iter)
            {
                const auto& clef = **iter;
                importClef( clef );
            }
        }
        
        
        void MeasureReader::importClef( const core::Clef& inClef ) const
        {
            api::ClefData clefData;
            clefData.tickTimePosition = myCurrentCursor.tickTimePosition;
            auto converter = Converter{};
            clefData.symbol = converter.convert( inClef.getSign()->getValue() );
            
            if( inClef.getHasLine() )
            {
                clefData.line = inClef.getLine()->getValue().getValue();
            }
            else
            {
                switch (clefData.symbol)
                {
                    case api::ClefSymbol::g:
                        clefData.line = 2;
                        break;
                    case api::ClefSymbol::f:
                        clefData.line = 4;
                        break;
                    case api::ClefSymbol::c:
                        clefData.line = 3;
                        break;
                    case api::ClefSymbol::jianpu:
                        clefData.line = 1;
                        break;
                    case api::ClefSymbol::tab:
                        clefData.line = 1;
                        break;
                    case api::ClefSymbol::percussion:
                        clefData.line = 3;
                        break;
                    default:
                        clefData.line = 3;
                        break;
                }
            }
            
            if( inClef.getHasClefOctaveChange() )
            {
                clefData.octaveChange = inClef.getClefOctaveChange()->getValue().getValue();
            }
            else
            {
                clefData.octaveChange = 0;
            }
            
            const auto& attr = *inClef.getAttributes();
            
            int celfStaffIndex = -1;
            if( attr.hasNumber )
            {
                celfStaffIndex = attr.number.getValue() - 1;
            }
            else
            {
                celfStaffIndex = 0;
            }
            
            if( myCurrentCursor.tickTimePosition == 0 )
            {
                if( attr.hasAfterBarline )
                {
                    if( attr.afterBarline == core::YesNo::yes )
                    {
                        clefData.location = api::ClefLocation::afterBarline;
                    }
                    else
                    {
                        clefData.location = api::ClefLocation::beforeBarline;
                    }
                }
                else
                {
                    clefData.location = api::ClefLocation::unspecified;
                }
            }
            else
            {
                clefData.location = api::ClefLocation::midMeasure;
            }
            insertClef( std::move( clefData ), celfStaffIndex );
        }
    
        
        void MeasureReader::insertNoteData( api::NoteData&& noteData, int staff, int voice ) const
        {
            MX_ASSERT( staff >= 0 );
            MX_ASSERT( static_cast<size_t>( staff ) < myOutMeasureData.staves.size() );
            auto& staffRef = myOutMeasureData.staves.at( static_cast<size_t>( staff ) );
            
            if( staffRef.voices.find( voice ) == staffRef.voices.cend() )
            {
                staffRef.voices[voice] = api::VoiceData{};
            }
            auto& voiceRef = staffRef.voices[voice];
            voiceRef.notes.emplace_back( std::move( noteData ) );
        }
        
        
        void MeasureReader::insertClef( api::ClefData&& clefData, int staff ) const
        {
            MX_ASSERT( staff >= 0 );
            MX_ASSERT( static_cast<size_t>( staff ) < myOutMeasureData.staves.size() );
            auto& staffRef = myOutMeasureData.staves.at( static_cast<size_t>( staff ) );
            staffRef.clefs.emplace_back( std::move( clefData ) );
        }
        
        void MeasureReader::consolidateVoicesForAllStaves() const
        {
            for( auto& staff : myOutMeasureData.staves )
            {
                if( isUserRequestedVoiceNumberConsistentAccrossAllVoices( staff ) )
                {
                    takeUserRequestedVoiceNumbers( staff );
                }
                else
                {
                    collapseVoicesAutomatically( staff );
                }
            }
        }
        
        
        void MeasureReader::takeUserRequestedVoiceNumbers( api::StaffData& staff ) const
        {
            std::map<int, api::VoiceData> newVoiceData;
            for( const auto& voicePair : staff.voices )
            {
                const int userRequestedVoiceNumber = getUserRequestedVoiceNumber( voicePair.second );
                MX_ASSERT( userRequestedVoiceNumber >= 1 );
                newVoiceData[userRequestedVoiceNumber-1] = std::move(voicePair.second);
                
            }
            staff.voices = std::move( newVoiceData );
        }
        
        
        void MeasureReader::collapseVoicesAutomatically( api::StaffData& staff ) const
        {
            std::map<int, api::VoiceData> newVoiceData;
            int newVoiceIndex = 0;
            for( auto& voicePair : staff.voices )
            {
                newVoiceData[newVoiceIndex] = std::move(voicePair.second);
                ++newVoiceIndex;
            }
            staff.voices = std::move( newVoiceData );
        }
        
        
        bool MeasureReader::isUserRequestedVoiceNumberConsistent( const api::VoiceData& voiceData ) const
        {
            if( voiceData.notes.empty() )
            {
                return true;
            }
            
            const int userRequestedVoiceNumber = voiceData.notes.front().userRequestedVoiceNumber;
            
            if( userRequestedVoiceNumber < 1 )
            {
                return false;
            }
            
            for( const auto& note : voiceData.notes )
            {
                if( note.userRequestedVoiceNumber != userRequestedVoiceNumber )
                {
                    return false;
                }
            }
            return true;
        }
        
        
        bool MeasureReader::isUserRequestedVoiceNumberConsistentAccrossAllVoices( const api::StaffData& staff ) const
        {
            std::set<int> userRequestedVoiceNumbers;
            for( const auto& voicePair : staff.voices )
            {
                if( !isUserRequestedVoiceNumberConsistent( voicePair.second ) )
                {
                    return false;
                }
                const int userRequestedVoiceNumber = getUserRequestedVoiceNumber( voicePair.second );
                auto result = userRequestedVoiceNumbers.insert( userRequestedVoiceNumber );
                
                if( !result.second )
                {
                    return false;
                }
            }
            return true;
        }
        
        
        int MeasureReader::getUserRequestedVoiceNumber( const api::VoiceData& voiceData ) const
        {
            if( voiceData.notes.empty() )
            {
                return -1;
            }
            
            return voiceData.notes.front().userRequestedVoiceNumber;
        }
    }
}
