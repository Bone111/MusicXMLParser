// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/FeatureAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        FeatureAttributes::FeatureAttributes()
        :type()
        ,hasType( false )
        {}


        bool FeatureAttributes::hasValues() const
        {
            return hasType;
        }


        std::ostream& FeatureAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, type, "type", hasType );
            }
            return os;
        }


        bool FeatureAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "FeatureAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, type, hasType, "type" ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
