// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/StaffSize.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        StaffSize::StaffSize()
        :myValue()
        {}


        StaffSize::StaffSize( const NonNegativeDecimal& value )
        :myValue( value )
        {}


        bool StaffSize::hasAttributes() const
        {
            return false;
        }


        bool StaffSize::hasContents() const
        {
            return true;
        }


        std::ostream& StaffSize::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& StaffSize::streamName( std::ostream& os ) const
        {
            os << "staff-size";
            return os;
        }


        std::ostream& StaffSize::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        NonNegativeDecimal StaffSize::getValue() const
        {
            return myValue;
        }


        void StaffSize::setValue( const NonNegativeDecimal& value )
        {
            myValue = value;
        }


        bool StaffSize::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.parse( xelement.getValue() );
            return true;
        }

    }
}
