// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/MidiDeviceAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        MidiDeviceAttributes::MidiDeviceAttributes()
        :port()
        ,id()
        ,hasPort( false )
        ,hasId( false )
        {}


        bool MidiDeviceAttributes::hasValues() const
        {
            return hasPort ||
            hasId;
        }


        std::ostream& MidiDeviceAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, port, "port", hasPort );
                streamAttribute( os, id, "id", hasId );
            }
            return os;
        }


        bool MidiDeviceAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "MidiDeviceAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, port, hasPort, "port" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, id, hasId, "id" ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
