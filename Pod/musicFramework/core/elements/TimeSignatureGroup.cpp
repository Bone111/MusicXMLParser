// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/TimeSignatureGroup.h"
#include "../../core/FromXElement.h"
#include "../../core/elements/BeatType.h"
#include "../../core/elements/Beats.h"
#include "../../core/elements/Interchangeable.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        TimeSignatureGroup::TimeSignatureGroup()
        :myBeats( makeBeats() )
        ,myBeatType( makeBeatType() )
        ,myInterchangeable( makeInterchangeable() )
        ,myHasInterchangeable( false )
        {}


        bool TimeSignatureGroup::hasAttributes() const
        {
            return false;
        }


        std::ostream& TimeSignatureGroup::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& TimeSignatureGroup::streamName( std::ostream& os ) const
        {
            return os;
        }


        bool TimeSignatureGroup::hasContents() const
        {
            return true;
        }


        std::ostream& TimeSignatureGroup::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            isOneLineOnly = false;
            myBeats->toStream( os, indentLevel );
            os << std::endl;
            myBeatType->toStream( os, indentLevel );
            if ( myHasInterchangeable )
            {
                os << std::endl;
                myInterchangeable->toStream( os, indentLevel );
            }
            return os;
        }


        BeatsPtr TimeSignatureGroup::getBeats() const
        {
            return myBeats;
        }


        void TimeSignatureGroup::setBeats( const BeatsPtr& value )
        {
            if ( value )
            {
                myBeats = value;
            }
        }


        BeatTypePtr TimeSignatureGroup::getBeatType() const
        {
            return myBeatType;
        }


        void TimeSignatureGroup::setBeatType( const BeatTypePtr& value )
        {
            if ( value )
            {
                myBeatType = value;
            }
        }


        InterchangeablePtr TimeSignatureGroup::getInterchangeable() const
        {
            return myInterchangeable;
        }


        void TimeSignatureGroup::setInterchangeable( const InterchangeablePtr& value )
        {
            if( value )
            {
                myInterchangeable = value;
            }
        }


        bool TimeSignatureGroup::getHasInterchangeable() const
        {
            return myHasInterchangeable;
        }


        void TimeSignatureGroup::setHasInterchangeable( const bool value )
        {
            myHasInterchangeable = value;
        }

        
        MX_FROM_XELEMENT_UNUSED( TimeSignatureGroup );
    }
}
