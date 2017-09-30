// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/ArrowDirection.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        ArrowDirection::ArrowDirection()
        :myValue( ArrowDirectionEnum::up )
        {}


        ArrowDirection::ArrowDirection( const ArrowDirectionEnum& value )
        :myValue( value )
        {}


        bool ArrowDirection::hasAttributes() const
        {
            return false;
        }


        bool ArrowDirection::hasContents() const
        {
            return true;
        }


        std::ostream& ArrowDirection::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& ArrowDirection::streamName( std::ostream& os ) const
        {
            os << "arrow-direction";
            return os;
        }


        std::ostream& ArrowDirection::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        ArrowDirectionEnum ArrowDirection::getValue() const
        {
            return myValue;
        }


        void ArrowDirection::setValue( const ArrowDirectionEnum& value )
        {
            myValue = value;
        }


        bool ArrowDirection::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            myValue = parseArrowDirectionEnum( xelement.getValue() );
            return true;
        }

    }
}
