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

        MX_FORWARD_DECLARE_ELEMENT( StickLocation )

        inline StickLocationPtr makeStickLocation() { return std::make_shared<StickLocation>(); }
		inline StickLocationPtr makeStickLocation( const StickLocationEnum& value ) { return std::make_shared<StickLocation>( value ); }
		inline StickLocationPtr makeStickLocation( StickLocationEnum&& value ) { return std::make_shared<StickLocation>( std::move( value ) ); }

        class StickLocation : public ElementInterface
        {
        public:
            StickLocation();
            StickLocation( const StickLocationEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            StickLocationEnum getValue() const;
            void setValue( const StickLocationEnum& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            StickLocationEnum myValue;
        };
    }
}
