// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/OffsetAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        OffsetAttributes::OffsetAttributes()
        :sound()
        ,hasSound( false )
        {}


        bool OffsetAttributes::hasValues() const
        {
            return hasSound;
        }


        std::ostream& OffsetAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, sound, "sound", hasSound );
            }
            return os;
        }


        bool OffsetAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "OffsetAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, sound, hasSound, "sound", &parseYesNo ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
