// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"
#include "../../core/elements/PartSymbolAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( PartSymbolAttributes )
        MX_FORWARD_DECLARE_ELEMENT( PartSymbol )

        inline PartSymbolPtr makePartSymbol() { return std::make_shared<PartSymbol>(); }
		inline PartSymbolPtr makePartSymbol( const GroupSymbolValue& value ) { return std::make_shared<PartSymbol>( value ); }
		inline PartSymbolPtr makePartSymbol( GroupSymbolValue&& value ) { return std::make_shared<PartSymbol>( std::move( value ) ); }

        class PartSymbol : public ElementInterface
        {
        public:
            PartSymbol();
            PartSymbol( const GroupSymbolValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            PartSymbolAttributesPtr getAttributes() const;
            void setAttributes( const PartSymbolAttributesPtr& attributes );
            GroupSymbolValue getValue() const;
            void setValue( const GroupSymbolValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            GroupSymbolValue myValue;
            PartSymbolAttributesPtr myAttributes;
        };
    }
}
