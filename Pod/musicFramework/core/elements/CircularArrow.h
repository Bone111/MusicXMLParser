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

        MX_FORWARD_DECLARE_ELEMENT( CircularArrow )

        inline CircularArrowPtr makeCircularArrow() { return std::make_shared<CircularArrow>(); }
		inline CircularArrowPtr makeCircularArrow( const CircularArrowEnum& value ) { return std::make_shared<CircularArrow>( value ); }
		inline CircularArrowPtr makeCircularArrow( CircularArrowEnum&& value ) { return std::make_shared<CircularArrow>( std::move( value ) ); }

        class CircularArrow : public ElementInterface
        {
        public:
            CircularArrow();
            CircularArrow( const CircularArrowEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            CircularArrowEnum getValue() const;
            void setValue( const CircularArrowEnum& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            CircularArrowEnum myValue;
        };
    }
}
