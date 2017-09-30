// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Artificial.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Artificial::Artificial() : ElementInterface() {}


        bool Artificial::hasAttributes() const { return false; }


        bool Artificial::hasContents() const  { return false; }
        std::ostream& Artificial::streamAttributes( std::ostream& os ) const { return os; }
        std::ostream& Artificial::streamName( std::ostream& os ) const  { os << "artificial"; return os; }
        std::ostream& Artificial::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        bool Artificial::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            return true;
        }

    }
}
