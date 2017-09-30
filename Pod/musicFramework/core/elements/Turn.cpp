// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Turn.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Turn::Turn()
        :ElementInterface()
        ,myAttributes( std::make_shared<TurnAttributes>() )
        {}


        bool Turn::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool Turn::hasContents() const  { return false; }
        std::ostream& Turn::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& Turn::streamName( std::ostream& os ) const  { os << "turn"; return os; }
        std::ostream& Turn::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        TurnAttributesPtr Turn::getAttributes() const
        {
            return myAttributes;
        }


        void Turn::setAttributes( const TurnAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool Turn::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
