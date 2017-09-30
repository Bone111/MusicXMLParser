// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/RightMargin.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        RightMargin::RightMargin()
        :myValue()
        {}


        RightMargin::RightMargin( const TenthsValue& value )
        :myValue( value )
        {}


        bool RightMargin::hasAttributes() const
        {
            return false;
        }


        bool RightMargin::hasContents() const
        {
            return true;
        }


        std::ostream& RightMargin::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& RightMargin::streamName( std::ostream& os ) const
        {
            os << "right-margin";
            return os;
        }


        std::ostream& RightMargin::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        TenthsValue RightMargin::getValue() const
        {
            return myValue;
        }


        void RightMargin::setValue( const TenthsValue& value )
        {
            myValue = value;
        }


        bool RightMargin::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.parse( xelement.getValue() );
            return true;
        }

    }
}
