// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/InstrumentSound.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        InstrumentSound::InstrumentSound()
        :myValue()
        {}


        InstrumentSound::InstrumentSound( const XsString& value )
        :myValue( value )
        {}


        bool InstrumentSound::hasAttributes() const
        {
            return false;
        }


        bool InstrumentSound::hasContents() const
        {
            return true;
        }


        std::ostream& InstrumentSound::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& InstrumentSound::streamName( std::ostream& os ) const
        {
            os << "instrument-sound";
            return os;
        }


        std::ostream& InstrumentSound::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        XsString InstrumentSound::getValue() const
        {
            return myValue;
        }


        void InstrumentSound::setValue( const XsString& value )
        {
            myValue = value;
        }


        bool InstrumentSound::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.setValue( xelement.getValue() );
            return true;
        }

    }
}
