// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/TransposeAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        TransposeAttributes::TransposeAttributes()
        :number()
        ,hasNumber( false )
        {}


        bool TransposeAttributes::hasValues() const
        {
            return hasNumber;
        }


        std::ostream& TransposeAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, number, "number", hasNumber );
            }
            return os;
        }


        bool TransposeAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "TransposeAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, number, hasNumber, "number" ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
