// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/PreBend.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        PreBend::PreBend() : ElementInterface() {}


        bool PreBend::hasAttributes() const { return false; }


        bool PreBend::hasContents() const  { return false; }
        std::ostream& PreBend::streamAttributes( std::ostream& os ) const { return os; }
        std::ostream& PreBend::streamName( std::ostream& os ) const  { os << "pre-bend"; return os; }
        std::ostream& PreBend::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        bool PreBend::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            return true;
        }

    }
}
