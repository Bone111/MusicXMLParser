// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/WithBarAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( WithBarAttributes )
        MX_FORWARD_DECLARE_ELEMENT( WithBar )

        inline WithBarPtr makeWithBar() { return std::make_shared<WithBar>(); }
		inline WithBarPtr makeWithBar( const XsString& value ) { return std::make_shared<WithBar>( value ); }
		inline WithBarPtr makeWithBar( XsString&& value ) { return std::make_shared<WithBar>( std::move( value ) ); }

        class WithBar : public ElementInterface
        {
        public:
            WithBar();
            WithBar( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            WithBarAttributesPtr getAttributes() const;
            void setAttributes( const WithBarAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            WithBarAttributesPtr myAttributes;
        };
    }
}
