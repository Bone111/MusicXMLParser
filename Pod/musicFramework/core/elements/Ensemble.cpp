// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Ensemble.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Ensemble::Ensemble()
        :myValue()
        {}


        Ensemble::Ensemble( const PositiveIntegerOrEmpty& value )
        :myValue( value )
        {}


        bool Ensemble::hasAttributes() const
        {
            return false;
        }


        bool Ensemble::hasContents() const
        {
            return true;
        }


        std::ostream& Ensemble::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& Ensemble::streamName( std::ostream& os ) const
        {
            os << "ensemble";
            return os;
        }


        std::ostream& Ensemble::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        PositiveIntegerOrEmpty Ensemble::getValue() const
        {
            return myValue;
        }


        void Ensemble::setValue( const PositiveIntegerOrEmpty& value )
        {
            myValue = value;
        }


        bool Ensemble::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            MX_UNUSED( xelement );
            myValue.parse( xelement.getValue() );
            return true;
        }

    }
}
