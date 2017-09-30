// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Rights.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Rights::Rights()
        :myValue()
        ,myAttributes( std::make_shared<RightsAttributes>() )
        {}


        Rights::Rights( const XsString& value )
        :myValue( value )
        ,myAttributes( std::make_shared<RightsAttributes>() )
        {}


        bool Rights::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool Rights::hasContents() const
        {
            return true;
        }


        std::ostream& Rights::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& Rights::streamName( std::ostream& os ) const
        {
            os << "rights";
            return os;
        }


        std::ostream& Rights::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        RightsAttributesPtr Rights::getAttributes() const
        {
            return myAttributes;
        }


        void Rights::setAttributes( const RightsAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        XsString Rights::getValue() const
        {
            return myValue;
        }


        void Rights::setValue( const XsString& value )
        {
            myValue = value;
        }


        bool Rights::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            bool isSuccess = true;
            isSuccess &= myAttributes->fromXElement( message, xelement );
            myValue.setValue( xelement.getValue() );
            MX_RETURN_IS_SUCCESS;
        }

    }
}
