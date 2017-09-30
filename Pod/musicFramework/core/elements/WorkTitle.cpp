// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/WorkTitle.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        WorkTitle::WorkTitle()
        :myValue()
        {}


        WorkTitle::WorkTitle( const XsString& value )
        :myValue( value )
        {}


        bool WorkTitle::hasAttributes() const
        {
            return false;
        }


        bool WorkTitle::hasContents() const
        {
            return true;
        }


        std::ostream& WorkTitle::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& WorkTitle::streamName( std::ostream& os ) const
        {
            os << "work-title";
            return os;
        }


        std::ostream& WorkTitle::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        XsString WorkTitle::getValue() const
        {
            return myValue;
        }


        void WorkTitle::setValue( const XsString& value )
        {
            myValue = value;
        }


        bool WorkTitle::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.setValue( xelement.getValue() );
            return true;
        }

    }
}
