// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Accent.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Accent::Accent()
                :ElementInterface()
                ,myAttributes( std::make_shared<EmptyPlacementAttributes>() )
        {}


        bool Accent::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool Accent::hasContents() const  { return false; }
        std::ostream& Accent::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& Accent::streamName( std::ostream& os ) const  { os << "accent"; return os; }
        std::ostream& Accent::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        EmptyPlacementAttributesPtr Accent::getAttributes() const
        {
            return myAttributes;
        }


        void Accent::setAttributes( const EmptyPlacementAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool Accent::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
