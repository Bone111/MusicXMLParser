// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Decimals.h"
#include "../../core/elements/OffsetAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( OffsetAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Offset )

        inline OffsetPtr makeOffset() { return std::make_shared<Offset>(); }
		inline OffsetPtr makeOffset( const DivisionsValue& value ) { return std::make_shared<Offset>( value ); }
		inline OffsetPtr makeOffset( DivisionsValue&& value ) { return std::make_shared<Offset>( std::move( value ) ); }

        class Offset : public ElementInterface
        {
        public:
            Offset();
            Offset( const DivisionsValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            OffsetAttributesPtr getAttributes() const;
            void setAttributes( const OffsetAttributesPtr& attributes );
            DivisionsValue getValue() const;
            void setValue( const DivisionsValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            DivisionsValue myValue;
            OffsetAttributesPtr myAttributes;
        };
    }
}
