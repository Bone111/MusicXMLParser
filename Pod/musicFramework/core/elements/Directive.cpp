// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Directive.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Directive::Directive()
        :myAttributes( std::make_shared<DirectiveAttributes>() )
        ,myValue()
        {}


        Directive::Directive( const XsString& value )
        :myAttributes( std::make_shared<DirectiveAttributes>() )
        ,myValue( value )
        {}


        bool Directive::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        std::ostream& Directive::streamAttributes( std::ostream& os ) const
        {
            return myAttributes->toStream( os );
        }


        std::ostream& Directive::streamName( std::ostream& os ) const
        {
            os << "directive";
            return os;
        }


        bool Directive::hasContents() const
        {
            return true;
        }


        std::ostream& Directive::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            MX_UNUSED( isOneLineOnly );
            isOneLineOnly = true;
            core::toStream( os, myValue );
            return os;
        }


        DirectiveAttributesPtr Directive::getAttributes() const
        {
            return myAttributes;
        }


        void Directive::setAttributes( const DirectiveAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        XsString Directive::getValue() const
        {
            return myValue;
        }


        void Directive::setValue( const XsString& value )
        {
            myValue = value;
        }


        bool Directive::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            bool isSuccess = true;
            isSuccess &= myAttributes->fromXElement( message, xelement );
            myValue.setValue( xelement.getValue() );
            MX_RETURN_IS_SUCCESS;
        }

    }
}
