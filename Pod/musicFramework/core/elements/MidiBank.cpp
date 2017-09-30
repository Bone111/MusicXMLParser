// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/MidiBank.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        MidiBank::MidiBank()
        :myValue()
        {}


        MidiBank::MidiBank( const Midi16384& value )
        :myValue( value )
        {}


        bool MidiBank::hasAttributes() const
        {
            return false;
        }


        bool MidiBank::hasContents() const
        {
            return true;
        }


        std::ostream& MidiBank::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& MidiBank::streamName( std::ostream& os ) const
        {
            os << "midi-bank";
            return os;
        }


        std::ostream& MidiBank::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        Midi16384 MidiBank::getValue() const
        {
            return myValue;
        }


        void MidiBank::setValue( const Midi16384& value )
        {
            myValue = value;
        }


        bool MidiBank::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.parse( xelement.getValue() );
            return true;
        }

    }
}
