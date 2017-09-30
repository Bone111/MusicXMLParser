// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../impl/NoteFunctions.h"
#include "../api/MarkData.h"
#include "../api/SpannerData.h"
#include "../core/elements/Accent.h"
#include "../core/elements/AccidentalMark.h"
#include "../core/elements/Arpeggiate.h"
#include "../core/elements/Articulations.h"
#include "../core/elements/ArticulationsChoice.h"
#include "../core/elements/BreathMark.h"
#include "../core/elements/Caesura.h"
#include "../core/elements/DetachedLegato.h"
#include "../core/elements/Doit.h"
#include "../core/elements/Dynamics.h"
#include "../core/elements/EditorialGroup.h"
#include "../core/elements/Falloff.h"
#include "../core/elements/Fermata.h"
#include "../core/elements/Footnote.h"
#include "../core/elements/Glissando.h"
#include "../core/elements/Level.h"
#include "../core/elements/NonArpeggiate.h"
#include "../core/elements/Notations.h"
#include "../core/elements/NotationsChoice.h"
#include "../core/elements/Note.h"
#include "../core/elements/Ornaments.h"
#include "../core/elements/OtherArticulation.h"
#include "../core/elements/OtherNotation.h"
#include "../core/elements/Plop.h"
#include "../core/elements/Scoop.h"
#include "../core/elements/Slide.h"
#include "../core/elements/Slur.h"
#include "../core/elements/Spiccato.h"
#include "../core/elements/Staccatissimo.h"
#include "../core/elements/Staccato.h"
#include "../core/elements/Stress.h"
#include "../core/elements/StrongAccent.h"
#include "../core/elements/Technical.h"
#include "../core/elements/Tenuto.h"
#include "../core/elements/Tied.h"
#include "../core/elements/Tuplet.h"
#include "../core/elements/Unstress.h"
#include "../core/elements/EditorialVoiceGroup.h"
#include "../core/elements/Footnote.h"
#include "../core/FromXElement.h"
#include "../impl/AccidentalMarkFunctions.h"
#include "../impl/ArticulationsFunctions.h"
#include "../impl/CurveFunctions.h"
#include "../impl/DynamicsReader.h"
#include "../impl/NoteReader.h"
#include "../impl/OrnamentsFunctions.h"
#include "../impl/PositionFunctions.h"
#include "../impl/PrintFunctions.h"
#include "../impl/TechnicalFunctions.h"
#include "../impl/TimeReader.h"
#include "../impl/TupletReader.h"
#include "../utility/Throw.h"
#include "../impl/MarkDataFunctions.h"

#include <algorithm>

namespace mx
{
    namespace impl
    {
        NoteFunctions::NoteFunctions( const core::Note& inMxNote, impl::Cursor inCursor )
        : myNote{ inMxNote }
        , myCursor{ inCursor }
        , myOutNoteData{}
        , myConverter()
        {}
        
        
        api::NoteData NoteFunctions::parseNote( ) const
        {
            // lock it because we have the function marked as const
            // but we are writing to a mutable NoteData (for convenience)
            std::lock_guard<std::mutex> guard{ myMutex };
            myOutNoteData = api::NoteData{};
            impl::NoteReader reader{ myNote };
            
            if( reader.getIsRest() )
            {
                myOutNoteData.isRest = true;
                myOutNoteData.isMeasureRest = reader.getIsMeasureRest();
            }
            
            myOutNoteData.isUnpitched = reader.getIsUnpitched();
            myOutNoteData.isDisplayStepOctaveSpecified = reader.getIsDisplayStepOctaveSpecified();
            myOutNoteData.isChord = reader.getIsChord();
            
            if( reader.getIsCue() )
            {
                myOutNoteData.noteType = api::NoteType::cue;
            }
            
            if( reader.getIsGrace() )
            {
                myOutNoteData.noteType = api::NoteType::grace;
            }
            
            if( reader.getIsNormal() )
            {
                myOutNoteData.noteType = api::NoteType::normal;
            }
            auto converter = Converter{};
            myOutNoteData.pitchData.step = converter.convert( reader.getStep() );
            myOutNoteData.pitchData.alter = reader.getAlter();
            
            myOutNoteData.pitchData.accidental = api::Accidental::none;
            
            if( reader.getHasAccidental() )
            {
                myOutNoteData.pitchData.accidental = converter.convert( reader.getAccidental() );
                myOutNoteData.pitchData.isAccidentalParenthetical = reader.getIsAccidentalParenthetical();
                myOutNoteData.pitchData.isAccidentalCautionary = reader.getIsAccidentalCautionary();
                myOutNoteData.pitchData.isAccidentalEditorial = reader.getIsAccidentalEditorial();
                myOutNoteData.pitchData.isAccidentalBracketed = reader.getIsAccidentalBracketed();
            }
            
            myOutNoteData.pitchData.octave = reader.getOctave();
            //myOutNoteData.staffIndex = reader.getStaffNumber() - 1;
            myOutNoteData.userRequestedVoiceNumber = reader.getVoiceNumber();
            
            if( reader.getIsDurationTypeSpecified() )
            {
                myOutNoteData.durationData.durationName = converter.convert( reader.getDurationType() );
            }
            else
            {
                myOutNoteData.durationData.durationName = deriveNoteTypeFromDurationValue( reader );
            }
            
            myOutNoteData.durationData.durationDots = reader.getNumDots();
            myOutNoteData.durationData.durationTimeTicks = myCursor.convertDurationToGlobalTickScale( reader.getDurationValue() );
            myOutNoteData.tickTimePosition = myCursor.tickTimePosition;
            
            for( const auto& coreBeamVal : reader.getBeams() )
            {
                myOutNoteData.beams.push_back( converter.convert( coreBeamVal ) );
            }
            
            myOutNoteData.durationData.timeModificationActualNotes = reader.getTimeModificationActualNotes();
            myOutNoteData.durationData.timeModificationNormalNotes = reader.getTimeModificationNormalNotes();
            myOutNoteData.durationData.timeModificationNormalType = converter.convert( reader.getTimeModificationNormalType() );
            myOutNoteData.durationData.timeModificationNormalTypeDots = reader.getTimeModificationNormalTypeDots();

            const core::NoteTypeValue timeModType = reader.getTimeModificationNormalType();
            const int timeModTypeDots = reader.getTimeModificationNormalTypeDots();
            bool isTimeModTypeSpecified = ( timeModTypeDots > 0 ) && ( timeModType != reader.getDurationType() );
            
            if( isTimeModTypeSpecified )
            {
                myOutNoteData.durationData.timeModificationNormalType = converter.convert( timeModType );
                myOutNoteData.durationData.timeModificationNormalTypeDots = timeModTypeDots;
            }
            else
            {
                myOutNoteData.durationData.timeModificationNormalType = api::DurationName::unspecified;
                myOutNoteData.durationData.timeModificationNormalTypeDots = 0;
            }
            parseNotations();
            myOutNoteData.positionData = impl::getPositionData( *myNote.getAttributes() );
            myOutNoteData.printData = impl::getPrintData( *myNote.getAttributes() );
            
            if( reader.getIsStemSpecified() )
            {
                myOutNoteData.stem = converter.convert( reader.getStem() );
            }
            myOutNoteData.isTieStart = reader.getIsTieStart();
            myOutNoteData.isTieStop = reader.getIsTieStop();

            parseMiscData();

            return myOutNoteData;
        }
        
        // TODO - make this work even if notes are dotted and if they are tupleted
        api::DurationName NoteFunctions::deriveNoteTypeFromDurationValue( const NoteReader& reader ) const
        {
            const long double durationValue = reader.getDurationValue();
            const long double ticksPerQuarter = static_cast<long double>( myCursor.getGlobalTicksPerQuarter() );
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_QUARTER * ticksPerQuarter ) )
            {
                return api::DurationName::quarter;
            }
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_HALF * ticksPerQuarter ) )
            {
                return api::DurationName::half;
            }
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_WHOLE * ticksPerQuarter ) )
            {
                return api::DurationName::whole;
            }
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_EIGHTH * ticksPerQuarter ) )
            {
                return api::DurationName::eighth;
            }
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_16TH * ticksPerQuarter ) )
            {
                return api::DurationName::dur16th;
            }
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_32ND * ticksPerQuarter ) )
            {
                return api::DurationName::dur32nd;
            }
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_64TH * ticksPerQuarter ) )
            {
                return api::DurationName::dur64th;
            }
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_128TH * ticksPerQuarter ) )
            {
                return api::DurationName::dur128th;
            }
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_512TH * ticksPerQuarter ) )
            {
                return api::DurationName::dur512th;
            }
            
            if( api::areSame( durationValue, api::DUR_QUARTERS_VALUE_1024TH * ticksPerQuarter ) )
            {
                return api::DurationName::dur1024th;
            }

            return api::DurationName::unspecified;
        }
        
        
        void NoteFunctions::parseNotations() const
        {
            for( const auto& notationsPtr : myNote.getNotationsSet() )
            {
                for( const auto& notationsChoicePtr : notationsPtr->getNotationsChoiceSet() )
                {
                    const auto& notationsChoice = *notationsChoicePtr;
                    const auto choice = notationsChoice.getChoice();
                    
                    switch (choice)
                    {
                        case core::NotationsChoice::Choice::tied:
                        {
                            parseCurve( *notationsChoice.getTied(), myOutNoteData );
                            break;
                        }
                        case core::NotationsChoice::Choice::slur:
                        {
                            parseCurve( *notationsChoice.getSlur(), myOutNoteData );
                            break;
                        }
                        case core::NotationsChoice::Choice::tuplet:
                        {
                            TupletReader reader{ *notationsChoice.getTuplet(), myCursor, myNote };
                            reader.parseTuplet( myOutNoteData.noteAttachmentData.tupletStarts, myOutNoteData.noteAttachmentData.tupletStops );
                            break;
                        }
                        case core::NotationsChoice::Choice::slide:
                        {
//                            const auto& slide = *notationsChoice.getSlide();
//                            const auto& attr = *slide.getAttributes();
//                            const auto slideType = attr.type;

//                            api::SpannerData spannerData;
//                            spannerData.name = "slide";
//                            spannerData.spannerType = api::SpannerType::slide;
//                            spannerData.tickTimePosition = myCursor.tickTimePosition;
//                            
//                            if( attr.hasNumber )
//                            {
//                                spannerData.numberLevel = attr.number.getValue();
//                            }
//
//                            if( slideType == core::StartStop::start )
//                            {
//                                myOutNoteData.noteAttachmentData.spannerStarts.emplace_back( std::move( spannerData ) );
//                            }
//                            else
//                            {
//                                myOutNoteData.noteAttachmentData.spannerStops.emplace_back( std::move( spannerData ) );
//                            }
                            
                            break;
                        }
                        case core::NotationsChoice::Choice::glissando:
                        {
                            break;
                        }
                        case core::NotationsChoice::Choice::ornaments:
                        {
                            // TODO - some ornaments should be treated as spanners instead of marks
                            OrnamentsFunctions funcs{ *notationsChoice.getOrnaments(), myCursor };
                            funcs.parseOrnaments( myOutNoteData.noteAttachmentData.marks );
                            break;
                        }
                        case core::NotationsChoice::Choice::technical:
                        {
                            // TODO - some technical items are spanners and others are complex/not-implemented yet
                            TechnicalFunctions funcs{ notationsChoice.getTechnical()->getTechnicalChoiceSet(), myCursor };
                            funcs.parseTechnicalMarks( myOutNoteData.noteAttachmentData.marks );
                            break;
                        }
                        case core::NotationsChoice::Choice::articulations:
                        {
                            ArticulationsFunctions funcs{ notationsChoice.getArticulations()->getArticulationsChoiceSet(), myCursor };
                            funcs.parseArticulations( myOutNoteData.noteAttachmentData.marks );
                            break;
                        }
                        case core::NotationsChoice::Choice::dynamics:
                        {
                            DynamicsReader funcs{ *notationsChoice.getDynamics(), myCursor };
                            funcs.parseDynamics( myOutNoteData.noteAttachmentData.marks );
                            break;
                        }
                        case core::NotationsChoice::Choice::fermata:
                        {
                            const auto& fermata = *notationsChoice.getFermata();
                            const auto& attr = *fermata.getAttributes();
                            const auto shape = fermata.getValue();
                            auto markType = api::MarkType::fermata;
                            
                            if( shape == core::FermataShape::emptystring )
                            {
                                if( !attr.hasType )
                                {
                                    markType = api::MarkType::fermata;
                                }
                                else if ( attr.type == core::UprightInverted::upright )
                                {
                                    markType = api::MarkType::fermataUpright;
                                }
                                else if ( attr.type == core::UprightInverted::inverted )
                                {
                                    markType = api::MarkType::fermataInverted;
                                }
                            }
                            else if( shape == core::FermataShape::normal )
                            {
                                if( !attr.hasType )
                                {
                                    markType = api::MarkType::fermataNormal;
                                }
                                else if ( attr.type == core::UprightInverted::upright )
                                {
                                    markType = api::MarkType::fermataNormalUpright;
                                }
                                else if ( attr.type == core::UprightInverted::inverted )
                                {
                                    markType = api::MarkType::fermataNormalInverted;
                                }
                                
                            }
                            else if( shape == core::FermataShape::angled )
                            {
                                if( !attr.hasType )
                                {
                                    markType = api::MarkType::fermataAngled;
                                }
                                else if ( attr.type == core::UprightInverted::upright )
                                {
                                    markType = api::MarkType::fermataAngledUpright;
                                }
                                else if ( attr.type == core::UprightInverted::inverted )
                                {
                                    markType = api::MarkType::fermataAngledInverted;
                                }
                            }
                            else if( shape == core::FermataShape::square )
                            {
                                if( !attr.hasType )
                                {
                                    markType = api::MarkType::fermataSquare;
                                }
                                else if ( attr.type == core::UprightInverted::upright )
                                {
                                    markType = api::MarkType::fermataSquareUpright;
                                }
                                else if ( attr.type == core::UprightInverted::inverted )
                                {
                                    markType = api::MarkType::fermataSquareInverted;
                                }
                            }
                            
                            // Unfortunately, without doing a lot of guess word, we can't
                            // know whether the correct glyph is "above" or "below"
                            api::MarkData markData{ markType };
                            impl::parseMarkDataAttributes( attr, markData );
                            markData.tickTimePosition = myCursor.tickTimePosition;
                            impl::parseMarkDataAttributes( attr, markData );
                            myOutNoteData.noteAttachmentData.marks.emplace_back( std::move( markData ) );
                            break;
                        }
                        case core::NotationsChoice::Choice::arpeggiate:
                        {
                            // TODO - import arpeggiate
                            break;
                        }
                        case core::NotationsChoice::Choice::nonArpeggiate:
                        {
                            // TODO - import non-arpeggiate
                            break;
                        }
                        case core::NotationsChoice::Choice::accidentalMark:
                        {
                            AccidentalMarkFunctions funcs{ *notationsChoice.getAccidentalMark(), myCursor };
                            myOutNoteData.noteAttachmentData.marks.emplace_back( funcs.parseAccidentalMark() );
                            break;
                        }
                        case core::NotationsChoice::Choice::otherNotation:
                        {
                            // TODO - import otherNotation
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        void NoteFunctions::parseMiscData() const
        {
            if (!myNote.getEditorialVoiceGroup()->getHasFootnote())
            {
                return;
            }

            auto footnote = myNote.getEditorialVoiceGroup()->getFootnote();

            if( footnote->getValue().getValue().size() > 0 )
            {
                // we expect this element to be unused if it is
                // stuffed with ##misc-data## in the font-family
                return;
            }

            auto attr = footnote->getAttributes();

            if( !attr->hasFontFamily )
            {
                return;
            }

            auto& miscData = attr->fontFamily;
            auto iter = miscData.getValuesBeginConst();
            const auto end = miscData.getValuesEndConst();

            if( iter == end )
            {
                return;
            }

            const auto firstString = iter->getValue();

            if( firstString.substr(0,13) != "##misc-data##" )
            {
                return;
            }

            myOutNoteData.miscData.push_back( firstString.substr( 13 ) );
            ++iter;

            for( ; iter != end; ++iter)
            {
                myOutNoteData.miscData.push_back( iter->getValue() );
            }
        }
    }
}
