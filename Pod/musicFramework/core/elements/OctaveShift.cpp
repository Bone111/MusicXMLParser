// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/OctaveShift.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        OctaveShift::OctaveShift()
        :ElementInterface()
        ,myAttributes( std::make_shared<OctaveShiftAttributes>() )
        {}


        bool OctaveShift::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool OctaveShift::hasContents() const  { return false; }
        std::ostream& OctaveShift::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& OctaveShift::streamName( std::ostream& os ) const  { os << "octave-shift"; return os; }
        std::ostream& OctaveShift::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        OctaveShiftAttributesPtr OctaveShift::getAttributes() const
        {
            return myAttributes;
        }


        void OctaveShift::setAttributes( const OctaveShiftAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool OctaveShift::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
