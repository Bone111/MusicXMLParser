// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/GroupNameDisplayAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        GroupNameDisplayAttributes::GroupNameDisplayAttributes()
        :printObject( YesNo::no )
        ,hasPrintObject( false )
        {}


        bool GroupNameDisplayAttributes::hasValues() const
        {
            return hasPrintObject;
        }


        std::ostream& GroupNameDisplayAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, printObject, "print-object", hasPrintObject );
            }
            return os;
        }


        bool GroupNameDisplayAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "GroupNameDisplayAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, printObject, hasPrintObject, "print-object", &parseYesNo ) ) { continue; }
            }
        
        
            return isSuccess;
        }

    }
}
