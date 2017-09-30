// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/DegreeAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        DegreeAttributes::DegreeAttributes()
        :printObject( YesNo::no )
        ,hasPrintObject( false )
        {}


        bool DegreeAttributes::hasValues() const
        {
            return hasPrintObject;
        }


        std::ostream& DegreeAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, printObject, "print-object", hasPrintObject );
            }
            return os;
        }


        bool DegreeAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "DegreeAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, printObject, hasPrintObject, "print-object", &parseYesNo ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
