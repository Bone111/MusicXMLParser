// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/ArrowStyle.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        ArrowStyle::ArrowStyle()
        :myValue( ArrowStyleEnum::single )
        {}


        ArrowStyle::ArrowStyle( const ArrowStyleEnum& value )
        :myValue( value )
        {}


        bool ArrowStyle::hasAttributes() const
        {
            return false;
        }


        bool ArrowStyle::hasContents() const
        {
            return true;
        }


        std::ostream& ArrowStyle::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& ArrowStyle::streamName( std::ostream& os ) const
        {
            os << "arrow-style";
            return os;
        }


        std::ostream& ArrowStyle::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        ArrowStyleEnum ArrowStyle::getValue() const
        {
            return myValue;
        }


        void ArrowStyle::setValue( const ArrowStyleEnum& value )
        {
            myValue = value;
        }


        bool ArrowStyle::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            myValue = parseArrowStyleEnum( xelement.getValue() );
            return true;
        }

    }
}
