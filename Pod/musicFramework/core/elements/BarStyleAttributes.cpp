// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/BarStyleAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        BarStyleAttributes::BarStyleAttributes()
        :color()
        ,hasColor( false )
        {}


        bool BarStyleAttributes::hasValues() const
        {
            return hasColor;
        }


        std::ostream& BarStyleAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, color, "color", hasColor );
            }
            return os;
        }


        bool BarStyleAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "BarStyleAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, color, hasColor, "color" ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
