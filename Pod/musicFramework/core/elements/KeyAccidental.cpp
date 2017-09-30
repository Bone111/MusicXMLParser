// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/KeyAccidental.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        KeyAccidental::KeyAccidental()
        :myValue( AccidentalValue::natural )
        {}


        KeyAccidental::KeyAccidental( const AccidentalValue& value )
        :myValue( value )
        {}


        bool KeyAccidental::hasAttributes() const
        {
            return false;
        }


        bool KeyAccidental::hasContents() const
        {
            return true;
        }


        std::ostream& KeyAccidental::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& KeyAccidental::streamName( std::ostream& os ) const
        {
            os << "key-accidental";
            return os;
        }


        std::ostream& KeyAccidental::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        AccidentalValue KeyAccidental::getValue() const
        {
            return myValue;
        }


        void KeyAccidental::setValue( const AccidentalValue& value )
        {
            myValue = value;
        }


        bool KeyAccidental::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            myValue = parseAccidentalValue( xelement.getValue() );
            return true;
        }

    }
}
