// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Integers.h"
#include "../../core/elements/TupletNumberAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( TupletNumberAttributes )
        MX_FORWARD_DECLARE_ELEMENT( TupletNumber )

        inline TupletNumberPtr makeTupletNumber() { return std::make_shared<TupletNumber>(); }
		inline TupletNumberPtr makeTupletNumber( const NonNegativeInteger& value ) { return std::make_shared<TupletNumber>( value ); }
		inline TupletNumberPtr makeTupletNumber( NonNegativeInteger&& value ) { return std::make_shared<TupletNumber>( std::move( value ) ); }

        class TupletNumber : public ElementInterface
        {
        public:
            TupletNumber();
            TupletNumber( const NonNegativeInteger& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            TupletNumberAttributesPtr getAttributes() const;
            void setAttributes( const TupletNumberAttributesPtr& attributes );
            NonNegativeInteger getValue() const;
            void setValue( const NonNegativeInteger& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            NonNegativeInteger myValue;
            TupletNumberAttributesPtr myAttributes;
        };
    }
}
