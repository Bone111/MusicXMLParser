// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/FootnoteAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( FootnoteAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Footnote )

        inline FootnotePtr makeFootnote() { return std::make_shared<Footnote>(); }
		inline FootnotePtr makeFootnote( const XsString& value ) { return std::make_shared<Footnote>( value ); }
		inline FootnotePtr makeFootnote( XsString&& value ) { return std::make_shared<Footnote>( std::move( value ) ); }

        class Footnote : public ElementInterface
        {
        public:
            Footnote();
            Footnote( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            FootnoteAttributesPtr getAttributes() const;
            void setAttributes( const FootnoteAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            FootnoteAttributesPtr myAttributes;
        };
    }
}
