// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Chromatic.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Chromatic::Chromatic()
        :myValue()
        {}


        Chromatic::Chromatic( const Semitones& value )
        :myValue( value )
        {}


        bool Chromatic::hasAttributes() const
        {
            return false;
        }


        bool Chromatic::hasContents() const
        {
            return true;
        }


        std::ostream& Chromatic::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& Chromatic::streamName( std::ostream& os ) const
        {
            os << "chromatic";
            return os;
        }


        std::ostream& Chromatic::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        Semitones Chromatic::getValue() const
        {
            return myValue;
        }


        void Chromatic::setValue( const Semitones& value )
        {
            myValue = value;
        }


        bool Chromatic::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.parse( xelement.getValue() );
            return true;
        }

    }
}
