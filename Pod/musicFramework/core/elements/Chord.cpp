// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Chord.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Chord::Chord() : ElementInterface() {}


        bool Chord::hasAttributes() const { return false; }


        bool Chord::hasContents() const  { return false; }
        std::ostream& Chord::streamAttributes( std::ostream& os ) const { return os; }
        std::ostream& Chord::streamName( std::ostream& os ) const  { os << "chord"; return os; }
        std::ostream& Chord::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        bool Chord::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            return true;
        }

    }
}
