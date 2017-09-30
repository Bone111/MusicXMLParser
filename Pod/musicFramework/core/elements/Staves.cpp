// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Staves.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Staves::Staves()
        :myValue()
        {}


        Staves::Staves( const NonNegativeInteger& value )
        :myValue( value )
        {}


        bool Staves::hasAttributes() const
        {
            return false;
        }


        bool Staves::hasContents() const
        {
            return true;
        }


        std::ostream& Staves::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& Staves::streamName( std::ostream& os ) const
        {
            os << "staves";
            return os;
        }


        std::ostream& Staves::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        NonNegativeInteger Staves::getValue() const
        {
            return myValue;
        }


        void Staves::setValue( const NonNegativeInteger& value )
        {
            myValue = value;
        }


        bool Staves::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.parse( xelement.getValue() );
            return true;
        }

    }
}
