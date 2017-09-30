// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/CreditImage.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        CreditImage::CreditImage()
        :ElementInterface()
        ,myAttributes( std::make_shared<CreditImageAttributes>() )
        {}


        bool CreditImage::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool CreditImage::hasContents() const  { return false; }
        std::ostream& CreditImage::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& CreditImage::streamName( std::ostream& os ) const  { os << "credit-image"; return os; }
        std::ostream& CreditImage::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        CreditImageAttributesPtr CreditImage::getAttributes() const
        {
            return myAttributes;
        }


        void CreditImage::setAttributes( const CreditImageAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool CreditImage::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
