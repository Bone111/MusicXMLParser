// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/DoubleTongue.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        DoubleTongue::DoubleTongue()
        :ElementInterface()
        ,myAttributes( std::make_shared<EmptyPlacementAttributes>() )
        {}


        bool DoubleTongue::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool DoubleTongue::hasContents() const  { return false; }
        std::ostream& DoubleTongue::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& DoubleTongue::streamName( std::ostream& os ) const  { os << "double-tongue"; return os; }
        std::ostream& DoubleTongue::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        EmptyPlacementAttributesPtr DoubleTongue::getAttributes() const
        {
            return myAttributes;
        }


        void DoubleTongue::setAttributes( const EmptyPlacementAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool DoubleTongue::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
