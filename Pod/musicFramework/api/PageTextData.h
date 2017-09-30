// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/ApiCommon.h"
#include "../api/PositionData.h"

#include <string>
#include <vector>

namespace mx
{
    namespace api
    {
        
        // distance values are in 'tenths' governed by the 'scaling' values

        class PageTextData
        {
        public:
            std::string text;
            int pageNumber;
            PositionData positionData;
            std::string description; // e.g. 'composer', 'page number', 'title', etc., this is metadata which does not appear on the printed page
        };
        
        MXAPI_EQUALS_BEGIN( PageTextData )
        MXAPI_EQUALS_MEMBER( text )
        MXAPI_EQUALS_MEMBER( pageNumber )
        MXAPI_EQUALS_MEMBER( positionData )
        MXAPI_EQUALS_MEMBER( description )
        MXAPI_EQUALS_END;
        MXAPI_NOT_EQUALS_AND_VECTORS( PageTextData );
    }
}
