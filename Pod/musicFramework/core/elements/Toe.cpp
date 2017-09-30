// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Toe.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Toe::Toe()
        :myAttributes( std::make_shared<ToeAttributes>() )
        {}


        bool Toe::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        std::ostream& Toe::streamAttributes( std::ostream& os ) const
        {
            return myAttributes->toStream( os );
        }


        std::ostream& Toe::streamName( std::ostream& os ) const
        {
            os << "toe";
            return os;
        }


        bool Toe::hasContents() const
        {
            return false;
        }


        std::ostream& Toe::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        ToeAttributesPtr Toe::getAttributes() const
        {
            return myAttributes;
        }


        void Toe::setAttributes( const ToeAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool Toe::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
