// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Integers.h"
#include "../../core/elements/InversionAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( InversionAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Inversion )

        inline InversionPtr makeInversion() { return std::make_shared<Inversion>(); }
		inline InversionPtr makeInversion( const NonNegativeInteger& value ) { return std::make_shared<Inversion>( value ); }
		inline InversionPtr makeInversion( NonNegativeInteger&& value ) { return std::make_shared<Inversion>( std::move( value ) ); }

        class Inversion : public ElementInterface
        {
        public:
            Inversion();
            Inversion( const NonNegativeInteger& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            InversionAttributesPtr getAttributes() const;
            void setAttributes( const InversionAttributesPtr& attributes );
            NonNegativeInteger getValue() const;
            void setValue( const NonNegativeInteger& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            NonNegativeInteger myValue;
            InversionAttributesPtr myAttributes;
        };
    }
}
