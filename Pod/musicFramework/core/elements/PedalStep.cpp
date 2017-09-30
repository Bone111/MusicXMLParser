// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/PedalStep.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        PedalStep::PedalStep()
        :myValue( StepEnum::a )
        {}


        PedalStep::PedalStep( const StepEnum& value )
        :myValue( value )
        {}


        bool PedalStep::hasAttributes() const
        {
            return false;
        }


        bool PedalStep::hasContents() const
        {
            return true;
        }


        std::ostream& PedalStep::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& PedalStep::streamName( std::ostream& os ) const
        {
            os << "pedal-step";
            return os;
        }


        std::ostream& PedalStep::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        StepEnum PedalStep::getValue() const
        {
            return myValue;
        }


        void PedalStep::setValue( const StepEnum& value )
        {
            myValue = value;
        }


        bool PedalStep::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            MX_UNUSED( message );
            myValue = parseStepEnum( xelement.getValue() );
            return true;
        }

    }
}
