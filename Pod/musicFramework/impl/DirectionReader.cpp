// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../impl/DirectionReader.h"
#include "../core/elements/AccordionRegistration.h"
#include "../core/elements/Bracket.h"
#include "../core/elements/Coda.h"
#include "../core/elements/Damp.h"
#include "../core/elements/DampAll.h"
#include "../core/elements/Dashes.h"
#include "../core/elements/Direction.h"
#include "../core/elements/DirectionType.h"
#include "../core/elements/Dynamics.h"
#include "../core/elements/EditorialVoiceDirectionGroup.h"
#include "../core/elements/Eyeglasses.h"
#include "../core/elements/Footnote.h"
#include "../core/elements/HarpPedals.h"
#include "../core/elements/Image.h"
#include "../core/elements/Level.h"
#include "../core/elements/Metronome.h"
#include "../core/elements/OctaveShift.h"
#include "../core/elements/Offset.h"
#include "../core/elements/OtherDirection.h"
#include "../core/elements/Pedal.h"
#include "../core/elements/Percussion.h"
#include "../core/elements/PrincipalVoice.h"
#include "../core/elements/Rehearsal.h"
#include "../core/elements/Scordatura.h"
#include "../core/elements/Segno.h"
#include "../core/elements/Sound.h"
#include "../core/elements/Staff.h"
#include "../core/elements/StringMute.h"
#include "../core/elements/Voice.h"
#include "../core/elements/Wedge.h"
#include "../core/elements/Words.h"
#include "../impl/MetronomeReader.h"
#include "../impl/PrintFunctions.h"
#include "../api/WedgeData.h"
#include "../impl/SpannerFunctions.h"
#include "../impl/DynamicsReader.h"
#include "../impl/MarkDataFunctions.h"

namespace mx
{
    namespace impl
    {
        DirectionReader::DirectionReader( const core::Direction& inDirection, Cursor inCursor )
        : myDirection{ inDirection }
        , myCursor{ inCursor }
        , myConverter{}
        , myOutDirectionData{}
        {
            
        }

        
        api::DirectionData DirectionReader::getDirectionData()
        {
            myOutDirectionData = api::DirectionData{};
            myOutDirectionData.tickTimePosition = myCursor.tickTimePosition;
            myOutDirectionData.isStaffValueSpecified = !myDirection.getHasStaff();
           
            if( myDirection.getHasOffset() )
            {
                myOutDirectionData.isOffsetSpecified = true;
                myOutDirectionData.offset = static_cast<int>( std::ceil( myDirection.getOffset()->getValue().getValue() - 0.5 ) );
                if( myDirection.getOffset()->getAttributes()->hasSound )
                {
                    myOutDirectionData.offsetSound = myConverter.convert( myDirection.getOffset()->getAttributes()->sound );
                }
            }
            
            if( myDirection.getAttributes()->hasPlacement )
            {
                myOutDirectionData.placement = myConverter.convert( myDirection.getAttributes()->placement );
            }
            
            for ( const auto& dtPtr : myDirection.getDirectionTypeSet() )
            {
                const auto& dt = *dtPtr;
                parseDirectionType( dt );
            }
            
            api::DirectionData temp{ std::move( myOutDirectionData ) };
            myOutDirectionData = api::DirectionData{};
            return temp;
        }
        
        
        void DirectionReader::parseDirectionType( const core::DirectionType& directionType )
        {
            switch ( directionType.getChoice() )
            {
                case core::DirectionType::Choice::rehearsal:
                {
                    parseRehearsal( directionType );
                    break;
                }
                case core::DirectionType::Choice::segno:
                {
                    parseSegno( directionType );
                    break;
                }
                case core::DirectionType::Choice::words:
                {
                    parseWords( directionType );
                    break;
                }
                case core::DirectionType::Choice::coda:
                {
                    parseCoda( directionType );
                    break;
                }
                case core::DirectionType::Choice::wedge:
                {
                    parseWedge( directionType );
                    break;
                }
                case core::DirectionType::Choice::dynamics:
                {
                    parseDynamics( directionType );
                    break;
                }
                case core::DirectionType::Choice::dashes:
                {
                    parseDashes( directionType );
                    break;
                }
                case core::DirectionType::Choice::bracket:
                {
                    parseBracket( directionType );
                    break;
                }
                case core::DirectionType::Choice::pedal:
                {
                    parsePedal( directionType );
                    break;
                }
                case core::DirectionType::Choice::metronome:
                {
                    parseMetronome( directionType );
                    break;
                }
                case core::DirectionType::Choice::octaveShift:
                {
                    parseOctaveShift( directionType );
                    break;
                }
                case core::DirectionType::Choice::harpPedals:
                {
                    parseHarpPedals( directionType );
                    break;
                }
                case core::DirectionType::Choice::damp:
                {
                    parseDamp( directionType );
                    break;
                }
                case core::DirectionType::Choice::dampAll:
                {
                    parseRehearsal( directionType );
                    break;
                }
                case core::DirectionType::Choice::eyeglasses:
                {
                    parseEyeglasses( directionType );
                    break;
                }
                case core::DirectionType::Choice::stringMute:
                {
                    parseStringMute( directionType );
                    break;
                }
                case core::DirectionType::Choice::scordatura:
                {
                    parseScordatura( directionType );
                    break;
                }
                case core::DirectionType::Choice::image:
                {
                    parseImage( directionType );
                    break;
                }
                case core::DirectionType::Choice::principalVoice:
                {
                    parsePrincipalVoice( directionType );
                    break;
                }
                case core::DirectionType::Choice::accordionRegistration:
                {
                    parseAccordionRegistration( directionType );
                    break;
                }
                case core::DirectionType::Choice::percussion:
                {
                    parsePercussion( directionType );
                    break;
                }
                case core::DirectionType::Choice::otherDirection:
                {
                    parseOtherDirection( directionType );
                    break;
                }
                default: break;
            }
        }
       
        
        void DirectionReader::parseRehearsal( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseSegno( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseWords( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseCoda( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseWedge( const core::DirectionType& directionType)
        {
            const auto& wedge = *directionType.getWedge();
            const auto& attr = *wedge.getAttributes();
            const auto wedgeType = myConverter.convert( attr.type );
            const bool isSpreadSpecified = attr.hasSpread;
            const long double spread = attr.spread.getValue();
            auto positionData = getPositionData( attr );
            auto lineData = getLineData( attr );
            auto colorData = getColor( attr );
            
            if( attr.type == core::WedgeType::stop )
            {
                api::WedgeStop stop;
                if( attr.hasNumber )
                {
                    stop.numberLevel = attr.number.getValue();
                }
                if( isSpreadSpecified )
                {
                    stop.isSpreadSpecified = true;
                    stop.spread = spread;
                }
                stop.positionData = positionData;
                myOutDirectionData.wedgeStops.emplace_back( std::move( stop ) );
                return;
            }
            else
            {
                api::WedgeStart start;
                if( attr.hasNumber )
                {
                    start.numberLevel = attr.number.getValue();
                }
                if( isSpreadSpecified )
                {
                    start.isSpreadSpecified = true;
                    start.spread = spread;
                }
                start.wedgeType = wedgeType;
                start.positionData = positionData;
                start.lineData = lineData;
                start.colorData = colorData;
                myOutDirectionData.wedgeStarts.emplace_back( std::move( start ) );
            }
        }
        
        
        void DirectionReader::parseDynamics( const core::DirectionType& directionType )
        {
            for( const auto& dynamic : directionType.getDynamicsSet() )
            {
                DynamicsReader reader{ *dynamic, myCursor };
                reader.parseDynamics( myOutDirectionData.marks );
                //parseDynamic( *dynamic );
            }
        }
        
        
        void DirectionReader::parseDynamic( const core::Dynamics& dynamic )
        {
            auto mark = api::MarkData{};
            const auto valueObject = dynamic.getValue();
            mark.markType = myConverter.convertDynamic( valueObject.getValue() );
            mark.name = valueObject.getValueString();
            impl::parseMarkDataAttributes( *dynamic.getAttributes(), mark );
            
            auto placement = mark.positionData.placement;
            
            if( placement == api::Placement::unspecified )
            {
                placement = myOutDirectionData.placement;
            }
            
            if( valueObject.getValue() == core::DynamicsEnum::otherDynamics )
            {
                auto codePoint = api::Smufl::findCodepoint( mark.name );
                if( codePoint > 0 )
                {
                    mark.smuflCodepoint = codePoint;
                    mark.smuflName = mark.name;
                }
            }
            else
            {
                mark.smuflName = api::MarkSmufl::getName( mark.markType, placement );
                mark.smuflCodepoint = api::MarkSmufl::getCodepoint( mark.markType, placement );
            }
            myOutDirectionData.marks.emplace_back( std::move( mark ) );
        }
        
        
        void DirectionReader::parseDashes( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseBracket( const core::DirectionType& directionType)
        {
            const auto& bracket = *directionType.getBracket();
            const auto& attr = *bracket.getAttributes();
            
            if( attr.type == core::StartStopContinue::stop )
            {
                api::SpannerStop stop;
                stop.tickTimePosition = myCursor.tickTimePosition;
                stop.numberLevel = impl::checkNumber( &attr );
                stop.positionData = this->parsePositionData( attr );
                myOutDirectionData.bracketStops.emplace_back( std::move( stop ) );
                return;
            }
            else if( attr.type == core::StartStopContinue::start )
            {
                api::SpannerStart start;
                start.tickTimePosition = myCursor.tickTimePosition;
                start.numberLevel = impl::checkNumber( &attr );
                start.positionData = this->parsePositionData( attr );
                start.lineData = impl::getLineData( attr );
                start.printData = impl::getPrintData( attr );
                myOutDirectionData.bracketStarts.emplace_back( std::move( start ) );
                return;
            }
        }
        
        
        void DirectionReader::parsePedal( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseMetronome( const core::DirectionType& directionType)
        {
            const auto& metronome = *directionType.getMetronome();
            MetronomeReader reader{ metronome };
            myOutDirectionData.tempos.emplace_back( reader.getTempoData() );
        }
        
        
        void DirectionReader::parseOctaveShift( const core::DirectionType& directionType)
        {
            const auto& octaveShift = *directionType.getOctaveShift();
            auto& attr = *octaveShift.getAttributes();
            
            if( attr.type == core::UpDownStopContinue::continue_ )
            {
                // not supported
                return;
            }
            
            bool isStop = attr.type == core::UpDownStopContinue::stop;
            if( isStop )
            {
                auto stop = impl::getSpannerStop( attr );
                stop.tickTimePosition = myCursor.tickTimePosition;
                myOutDirectionData.ottavaStops.emplace_back( std::move( stop ) );
                return;
            }
            
            auto ottavaType = api::OttavaType::unspecified;
            int amount = 8;
            
            if( attr.hasSize )
            {
                amount = attr.size.getValue();
            }
            
            bool isUp = attr.type == core::UpDownStopContinue::up;
            
            if( isUp && amount > 8 )
            {
                ottavaType = api::OttavaType::o15ma;
            }
            else if ( isUp )
            {
                ottavaType = api::OttavaType::o8va;
            }
            else if ( !isUp && amount > 8 )
            {
                ottavaType = api::OttavaType::o15mb;
            }
            else if ( !isUp )
            {
                ottavaType = api::OttavaType::o8vb;
            }

            api::OttavaStart start;
            start.spannerStart = impl::getSpannerStart( attr );
            start.ottavaType = ottavaType;
            start.spannerStart.tickTimePosition = myCursor.tickTimePosition;
            myOutDirectionData.ottavaStarts.emplace_back( std::move( start ) );
        }
        
        
        void DirectionReader::parseHarpPedals( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseDamp( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseDampAll( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseEyeglasses( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseStringMute( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseScordatura( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseImage( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parsePrincipalVoice( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseAccordionRegistration( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parsePercussion( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
        
        
        void DirectionReader::parseOtherDirection( const core::DirectionType& directionType)
        {
            MX_UNUSED( directionType );
        }
    }
}
