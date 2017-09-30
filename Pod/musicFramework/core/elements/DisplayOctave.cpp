// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/DisplayOctave.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        DisplayOctave::DisplayOctave()
        :myValue()
        {}


        DisplayOctave::DisplayOctave( const OctaveValue& value )
        :myValue( value )
        {}


        bool DisplayOctave::hasAttributes() const
        {
            return false;
        }


        bool DisplayOctave::hasContents() const
        {
            return true;
        }


        std::ostream& DisplayOctave::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& DisplayOctave::streamName( std::ostream& os ) const
        {
            os << "display-octave";
            return os;
        }


        std::ostream& DisplayOctave::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        OctaveValue DisplayOctave::getValue() const
        {
            return myValue;
        }


        void DisplayOctave::setValue( const OctaveValue& value )
        {
            myValue = value;
        }


        bool DisplayOctave::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.parse( xelement.getValue() );
            return true;
        }

    }
}
