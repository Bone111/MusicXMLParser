// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Damp.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Damp::Damp()
        :ElementInterface()
        ,myAttributes( std::make_shared<EmptyPrintObjectStyleAlignAttributes>() )
        {}


        bool Damp::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool Damp::hasContents() const  { return false; }
        std::ostream& Damp::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& Damp::streamName( std::ostream& os ) const  { os << "damp"; return os; }
        std::ostream& Damp::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        EmptyPrintObjectStyleAlignAttributesPtr Damp::getAttributes() const
        {
            return myAttributes;
        }


        void Damp::setAttributes( const EmptyPrintObjectStyleAlignAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool Damp::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
