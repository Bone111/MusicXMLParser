// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Wedge.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Wedge::Wedge()
        :ElementInterface()
        ,myAttributes( std::make_shared<WedgeAttributes>() )
        {}


        bool Wedge::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool Wedge::hasContents() const  { return false; }
        std::ostream& Wedge::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& Wedge::streamName( std::ostream& os ) const  { os << "wedge"; return os; }
        std::ostream& Wedge::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        WedgeAttributesPtr Wedge::getAttributes() const
        {
            return myAttributes;
        }


        void Wedge::setAttributes( const WedgeAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool Wedge::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
