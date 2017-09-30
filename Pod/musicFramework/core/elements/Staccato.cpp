// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Staccato.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Staccato::Staccato()
        :ElementInterface()
        ,myAttributes( std::make_shared<EmptyPlacementAttributes>() )
        {}


        bool Staccato::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool Staccato::hasContents() const  { return false; }
        std::ostream& Staccato::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& Staccato::streamName( std::ostream& os ) const  { os << "staccato"; return os; }
        std::ostream& Staccato::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        EmptyPlacementAttributesPtr Staccato::getAttributes() const
        {
            return myAttributes;
        }


        void Staccato::setAttributes( const EmptyPlacementAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool Staccato::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
