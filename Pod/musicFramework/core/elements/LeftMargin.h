// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Decimals.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( LeftMargin )

        inline LeftMarginPtr makeLeftMargin() { return std::make_shared<LeftMargin>(); }
		inline LeftMarginPtr makeLeftMargin( const TenthsValue& value ) { return std::make_shared<LeftMargin>( value ); }
		inline LeftMarginPtr makeLeftMargin( TenthsValue&& value ) { return std::make_shared<LeftMargin>( std::move( value ) ); }

        class LeftMargin : public ElementInterface
        {
        public:
            LeftMargin();
            LeftMargin( const TenthsValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            TenthsValue getValue() const;
            void setValue( const TenthsValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            TenthsValue myValue;
        };
    }
}
