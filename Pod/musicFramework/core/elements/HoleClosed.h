// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"
#include "../../core/elements/HoleClosedAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( HoleClosedAttributes )
        MX_FORWARD_DECLARE_ELEMENT( HoleClosed )

        inline HoleClosedPtr makeHoleClosed() { return std::make_shared<HoleClosed>(); }
		inline HoleClosedPtr makeHoleClosed( const HoleClosedValue& value ) { return std::make_shared<HoleClosed>( value ); }
		inline HoleClosedPtr makeHoleClosed( HoleClosedValue&& value ) { return std::make_shared<HoleClosed>( std::move( value ) ); }

        class HoleClosed : public ElementInterface
        {
        public:
            HoleClosed();
            HoleClosed( const HoleClosedValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            HoleClosedAttributesPtr getAttributes() const;
            void setAttributes( const HoleClosedAttributesPtr& attributes );
            HoleClosedValue getValue() const;
            void setValue( const HoleClosedValue& value );
            
            bool fromXElement( std::ostream& message, xml::XElement& xelement );
            
        private:
            HoleClosedValue myValue;
            HoleClosedAttributesPtr myAttributes;
        };
    }
}
