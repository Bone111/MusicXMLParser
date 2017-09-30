// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Double.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Double::Double() : ElementInterface() {}


        bool Double::hasAttributes() const { return false; }


        bool Double::hasContents() const  { return false; }
        std::ostream& Double::streamAttributes( std::ostream& os ) const { return os; }
        std::ostream& Double::streamName( std::ostream& os ) const  { os << "double"; return os; }
        std::ostream& Double::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        bool Double::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            return true;
        }

    }
}
