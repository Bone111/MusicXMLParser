// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/DirectionData.h"
#include "../impl/Cursor.h"
#include "../impl/Converter.h"
#include "../impl/PositionFunctions.h"
#include "../core/elements/Direction.h"

#include <mutex>
#include <vector>

namespace mx
{
	namespace core
	{
        class DirectionType;
        using DirectionTypePtr = std::shared_ptr<DirectionType>;
        using DirectionTypeSet = std::vector<DirectionTypePtr>;
        class Dynamics;
	}
    namespace impl
    {
    	class DirectionReader
    	{
    	public:
            DirectionReader( const core::Direction& inDirection, Cursor inCursor );
            api::DirectionData getDirectionData();

    	private:
            const core::Direction& myDirection;
            const Cursor myCursor;
            const Converter myConverter;
            api::DirectionData myOutDirectionData;
            
    	private:
            void parseStaffIndex();
            void parseDirectionType( const core::DirectionType& directionType );
            void parseRehearsal( const core::DirectionType& directionType );
            void parseSegno( const core::DirectionType& directionType );
            void parseWords( const core::DirectionType& directionType );
            void parseCoda( const core::DirectionType& directionType );
            void parseWedge( const core::DirectionType& directionType );
            void parseDynamics( const core::DirectionType& directionType );
            void parseDynamic( const core::Dynamics& dynamic );
            void parseDashes( const core::DirectionType& directionType );
            void parseBracket( const core::DirectionType& directionType );
            void parsePedal( const core::DirectionType& directionType );
            void parseMetronome( const core::DirectionType& directionType );
            void parseOctaveShift( const core::DirectionType& directionType );
            void parseHarpPedals( const core::DirectionType& directionType );
            void parseDamp( const core::DirectionType& directionType );
            void parseDampAll( const core::DirectionType& directionType );
            void parseEyeglasses( const core::DirectionType& directionType );
            void parseStringMute( const core::DirectionType& directionType );
            void parseScordatura( const core::DirectionType& directionType );
            void parseImage( const core::DirectionType& directionType );
            void parsePrincipalVoice( const core::DirectionType& directionType );
            void parseAccordionRegistration( const core::DirectionType& directionType );
            void parsePercussion( const core::DirectionType& directionType );
            void parseOtherDirection( const core::DirectionType& directionType );
            
            template<typename ATTRIBUTES_TYPE>
            api::PositionData parsePositionData( const ATTRIBUTES_TYPE& attributes )
            {
                api::PositionData positionData = impl::getPositionData( attributes );
                
                if( positionData.placement == api::Placement::unspecified )
                {
                    const auto& dirAttr = *myDirection.getAttributes();
                    
                    if( dirAttr.hasPlacement )
                    {
                        positionData.placement = myConverter.convert( dirAttr.placement );
                    }
                }
                
                return positionData;
            }
    	};
	}
}
