// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( Glass )

        inline GlassPtr makeGlass() { return std::make_shared<Glass>(); }
		inline GlassPtr makeGlass( const GlassEnum& value ) { return std::make_shared<Glass>( value ); }
		inline GlassPtr makeGlass( GlassEnum&& value ) { return std::make_shared<Glass>( std::move( value ) ); }

        class Glass : public ElementInterface
        {
        public:
            Glass();
            Glass( const GlassEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            GlassEnum getValue() const;
            void setValue( const GlassEnum& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            GlassEnum myValue;
        };
    }
}
