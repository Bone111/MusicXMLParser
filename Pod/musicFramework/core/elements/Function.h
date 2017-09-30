// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/FunctionAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( FunctionAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Function )

        inline FunctionPtr makeFunction() { return std::make_shared<Function>(); }
		inline FunctionPtr makeFunction( const XsString& value ) { return std::make_shared<Function>( value ); }
		inline FunctionPtr makeFunction( XsString&& value ) { return std::make_shared<Function>( std::move( value ) ); }

        class Function : public ElementInterface
        {
        public:
            Function();
            Function( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            FunctionAttributesPtr getAttributes() const;
            void setAttributes( const FunctionAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            FunctionAttributesPtr myAttributes;
        };
    }
}
