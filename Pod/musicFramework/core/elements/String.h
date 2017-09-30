// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Integers.h"
#include "../../core/elements/StringAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( StringAttributes )
        MX_FORWARD_DECLARE_ELEMENT( String )

        inline StringPtr makeString() { return std::make_shared<String>(); }
        inline StringPtr makeString( const StringNumber& value ) { return std::make_shared<String>( value ); }
		inline StringPtr makeString( StringNumber&& value ) { return std::make_shared<String>( std::move( value ) ); }
        

        class String : public ElementInterface
        {
        public:
            String();
            String( const StringNumber& value );

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            StringAttributesPtr getAttributes() const;
            void setAttributes( const StringAttributesPtr& value );
            StringNumber getValue() const;
            void setValue( const StringNumber& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            StringAttributesPtr myAttributes;
            StringNumber myValue;
        };
    }
}
