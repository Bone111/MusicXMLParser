// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Tenths.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Tenths::Tenths()
        :myValue()
        {}


        Tenths::Tenths( const TenthsValue& value )
        :myValue( value )
        {}


        bool Tenths::hasAttributes() const
        {
            return false;
        }


        bool Tenths::hasContents() const
        {
            return true;
        }


        std::ostream& Tenths::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& Tenths::streamName( std::ostream& os ) const
        {
            os << "tenths";
            return os;
        }


        std::ostream& Tenths::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        TenthsValue Tenths::getValue() const
        {
            return myValue;
        }


        void Tenths::setValue( const TenthsValue& value )
        {
            myValue = value;
        }


        bool Tenths::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.parse( xelement.getValue() );
            return true;
        }

    }
}
