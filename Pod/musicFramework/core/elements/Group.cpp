// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Group.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Group::Group()
        :myValue()
        {}


        Group::Group( const XsString& value )
        :myValue( value )
        {}


        bool Group::hasAttributes() const
        {
            return false;
        }


        bool Group::hasContents() const
        {
            return true;
        }


        std::ostream& Group::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& Group::streamName( std::ostream& os ) const
        {
            os << "group";
            return os;
        }


        std::ostream& Group::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        XsString Group::getValue() const
        {
            return myValue;
        }


        void Group::setValue( const XsString& value )
        {
            myValue = value;
        }


        bool Group::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.setValue( xelement.getValue() );
            return true;
        }

    }
}
