// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/PlayAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        PlayAttributes::PlayAttributes()
        :id()
        ,hasId( false )
        {}


        bool PlayAttributes::hasValues() const
        {
            return hasId;
        }


        std::ostream& PlayAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, id, "id", hasId );
            }
            return os;
        }


        bool PlayAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "PlayAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, id, hasId, "id" ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
