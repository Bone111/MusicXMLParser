// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"
#include "../../core/elements/StemAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( StemAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Stem )

        inline StemPtr makeStem() { return std::make_shared<Stem>(); }
		inline StemPtr makeStem( const StemValue& value ) { return std::make_shared<Stem>( value ); }
		inline StemPtr makeStem( StemValue&& value ) { return std::make_shared<Stem>( std::move( value ) ); }

        class Stem : public ElementInterface
        {
        public:
            Stem();
            Stem( const StemValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            StemAttributesPtr getAttributes() const;
            void setAttributes( const StemAttributesPtr& attributes );
            StemValue getValue() const;
            void setValue( const StemValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            StemValue myValue;
            StemAttributesPtr myAttributes;
        };
    }
}
