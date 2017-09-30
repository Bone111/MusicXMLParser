// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/AccordionHigh.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        AccordionHigh::AccordionHigh() : ElementInterface() {}


        bool AccordionHigh::hasAttributes() const { return false; }


        bool AccordionHigh::hasContents() const  { return false; }
        std::ostream& AccordionHigh::streamAttributes( std::ostream& os ) const { return os; }
        std::ostream& AccordionHigh::streamName( std::ostream& os ) const  { os << "accordion-high"; return os; }
        std::ostream& AccordionHigh::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        bool AccordionHigh::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            return true;
        }

    }
}
