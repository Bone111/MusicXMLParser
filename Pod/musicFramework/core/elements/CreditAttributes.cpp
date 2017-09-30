// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/CreditAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        CreditAttributes::CreditAttributes()
        :page()
        ,hasPage( false )
        {}


        bool CreditAttributes::hasValues() const
        {
            return hasPage;
        }


        std::ostream& CreditAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, page, "page", hasPage );
            }
            return os;
        }


        bool CreditAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "CreditAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, page, hasPage, "page" ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
