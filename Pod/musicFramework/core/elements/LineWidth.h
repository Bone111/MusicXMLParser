// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Decimals.h"
#include "../../core/elements/LineWidthAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( LineWidthAttributes )
        MX_FORWARD_DECLARE_ELEMENT( LineWidth )

        inline LineWidthPtr makeLineWidth() { return std::make_shared<LineWidth>(); }
		inline LineWidthPtr makeLineWidth( const TenthsValue& value ) { return std::make_shared<LineWidth>( value ); }
		inline LineWidthPtr makeLineWidth( TenthsValue&& value ) { return std::make_shared<LineWidth>( std::move( value ) ); }

        class LineWidth : public ElementInterface
        {
        public:
            LineWidth();
            LineWidth( const TenthsValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            LineWidthAttributesPtr getAttributes() const;
            void setAttributes( const LineWidthAttributesPtr& attributes );
            TenthsValue getValue() const;
            void setValue( const TenthsValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            TenthsValue myValue;
            LineWidthAttributesPtr myAttributes;
        };
    }
}
