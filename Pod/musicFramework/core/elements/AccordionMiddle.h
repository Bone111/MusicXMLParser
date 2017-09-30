// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Integers.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( AccordionMiddle )

        inline AccordionMiddlePtr makeAccordionMiddle() { return std::make_shared<AccordionMiddle>(); }
		inline AccordionMiddlePtr makeAccordionMiddle( const AccordionMiddleValue& value ) { return std::make_shared<AccordionMiddle>( value ); }
		inline AccordionMiddlePtr makeAccordionMiddle( AccordionMiddleValue&& value ) { return std::make_shared<AccordionMiddle>( std::move( value ) ); }

        class AccordionMiddle : public ElementInterface
        {
        public:
            AccordionMiddle();
            AccordionMiddle( const AccordionMiddleValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            AccordionMiddleValue getValue() const;
            void setValue( const AccordionMiddleValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            AccordionMiddleValue myValue;
        };
    }
}
