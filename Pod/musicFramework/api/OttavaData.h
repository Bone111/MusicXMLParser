// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once
#include "../api/SpannerData.h"

namespace mx
{
    namespace api
    {
        enum class OttavaType
        {
            unspecified,
            o8va,        // octave up 
            o8vb,        // octave down
            o15ma,       // 2 octaves up
            o15mb        // 2 octaves down
        };

        class OttavaStart
        {
        public:
            SpannerStart spannerStart;
            OttavaType ottavaType;
            
            OttavaStart()
            : spannerStart{}
            , ottavaType{ OttavaType::unspecified }
            {
                
            }
        };
        
        // SpannerStop is used for OttavaStops
        
        MXAPI_EQUALS_BEGIN( OttavaStart )
        MXAPI_EQUALS_MEMBER( spannerStart )
        MXAPI_EQUALS_MEMBER( ottavaType )
        MXAPI_EQUALS_END;
        MXAPI_NOT_EQUALS_AND_VECTORS( OttavaStart );
    }
}
