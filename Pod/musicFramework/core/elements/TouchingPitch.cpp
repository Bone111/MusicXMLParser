// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/TouchingPitch.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        TouchingPitch::TouchingPitch() : ElementInterface() {}


        bool TouchingPitch::hasAttributes() const { return false; }


        bool TouchingPitch::hasContents() const  { return false; }
        std::ostream& TouchingPitch::streamAttributes( std::ostream& os ) const { return os; }
        std::ostream& TouchingPitch::streamName( std::ostream& os ) const  { os << "touching-pitch"; return os; }
        std::ostream& TouchingPitch::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        bool TouchingPitch::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            return true;
        }

    }
}
