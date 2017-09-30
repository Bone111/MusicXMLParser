// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Step.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Step::Step()
        :myValue( StepEnum::a )
        {}


        Step::Step( const StepEnum& value )
        :myValue( value )
        {}


        bool Step::hasAttributes() const
        {
            return false;
        }


        bool Step::hasContents() const
        {
            return true;
        }


        std::ostream& Step::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& Step::streamName( std::ostream& os ) const
        {
            os << "step";
            return os;
        }


        std::ostream& Step::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        StepEnum Step::getValue() const
        {
            return myValue;
        }


        void Step::setValue( const StepEnum& value )
        {
            myValue = value;
        }


        bool Step::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            myValue = parseStepEnum( xelement.getValue() );
            return true;
        }

    }
}
