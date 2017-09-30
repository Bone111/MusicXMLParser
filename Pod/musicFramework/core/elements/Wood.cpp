// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Wood.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Wood::Wood()
        :myValue( WoodEnum::claves )
        {}


        Wood::Wood( const WoodEnum& value )
        :myValue( value )
        {}


        bool Wood::hasAttributes() const
        {
            return false;
        }


        bool Wood::hasContents() const
        {
            return true;
        }


        std::ostream& Wood::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& Wood::streamName( std::ostream& os ) const
        {
            os << "wood";
            return os;
        }


        std::ostream& Wood::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        WoodEnum Wood::getValue() const
        {
            return myValue;
        }


        void Wood::setValue( const WoodEnum& value )
        {
            myValue = value;
        }


        bool Wood::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue = parseWoodEnum( xelement.getValue() );
            return true;
        }

    }
}
