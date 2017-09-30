// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Laughing.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Laughing::Laughing() : ElementInterface() {}


        bool Laughing::hasAttributes() const { return false; }


        bool Laughing::hasContents() const  { return false; }
        std::ostream& Laughing::streamAttributes( std::ostream& os ) const { return os; }
        std::ostream& Laughing::streamName( std::ostream& os ) const  { os << "laughing"; return os; }
        std::ostream& Laughing::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        bool Laughing::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            return true;
        }

    }
}
