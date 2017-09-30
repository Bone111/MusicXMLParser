// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/CreatorAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( CreatorAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Creator )

        inline CreatorPtr makeCreator() { return std::make_shared<Creator>(); }
		inline CreatorPtr makeCreator( const XsString& value ) { return std::make_shared<Creator>( value ); }
		inline CreatorPtr makeCreator( XsString&& value ) { return std::make_shared<Creator>( std::move( value ) ); }

        class Creator : public ElementInterface
        {
        public:
            Creator();
            Creator( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            CreatorAttributesPtr getAttributes() const;
            void setAttributes( const CreatorAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            CreatorAttributesPtr myAttributes;
        };
    }
}
