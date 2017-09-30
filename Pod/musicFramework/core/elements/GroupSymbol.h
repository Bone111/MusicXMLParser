// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"
#include "../../core/elements/GroupSymbolAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( GroupSymbolAttributes )
        MX_FORWARD_DECLARE_ELEMENT( GroupSymbol )

        inline GroupSymbolPtr makeGroupSymbol() { return std::make_shared<GroupSymbol>(); }
		inline GroupSymbolPtr makeGroupSymbol( const GroupSymbolValue& value ) { return std::make_shared<GroupSymbol>( value ); }
		inline GroupSymbolPtr makeGroupSymbol( GroupSymbolValue&& value ) { return std::make_shared<GroupSymbol>( std::move( value ) ); }

        class GroupSymbol : public ElementInterface
        {
        public:
            GroupSymbol();
            GroupSymbol( const GroupSymbolValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            GroupSymbolAttributesPtr getAttributes() const;
            void setAttributes( const GroupSymbolAttributesPtr& attributes );
            GroupSymbolValue getValue() const;
            void setValue( const GroupSymbolValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            GroupSymbolValue myValue;
            GroupSymbolAttributesPtr myAttributes;
        };
    }
}
