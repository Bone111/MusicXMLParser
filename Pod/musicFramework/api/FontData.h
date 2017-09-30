// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/ApiCommon.h"
#include "../api/PositionData.h"
#include "../api/FontData.h"

#include <string>
#include <vector>

namespace mx
{
    namespace api
    {
        
        enum class FontSizeType
        {
            unspecified,
            css,
            point
        };
        
        
        enum class CssSize
        {
            unspecified,
            xxSmall,
            xSmall,
            small,
            medium,
            large,
            xLarge,
            xxLarge
        };
        
        
        enum class FontStyle
        {
            unspecified,
            normal,
            italic
        };
        
        
        enum class FontWeight
        {
            unspecified,
            normal,
            bold
        };
        
        
        struct FontData
        {
            
            // fontSizeType indicates which fontSize field
            // is in use. if css, then use the fontSizeCss
            // field, if point then use fontSizePoint
            FontSizeType sizeType;
            long double sizePoint;
            CssSize sizeCss;
            
            FontStyle style;
            FontWeight weight;
            
            std::vector<std::string> fontFamily;
            
            int underline;
            int overline;
            int lineThrough;
            
            FontData()
            : sizeType{ FontSizeType::unspecified }
            , sizePoint{ -1.0L }
            , sizeCss{ CssSize::unspecified }
            , style{ FontStyle::unspecified }
            , weight{ FontWeight::unspecified }
            , fontFamily{}
            , underline{ 0 }
            , overline{ 0 }
            , lineThrough{ 0 }
            {
                
            }
        };
        
        
        MXAPI_EQUALS_BEGIN( FontData )
        MXAPI_EQUALS_MEMBER( sizeType )
        MXAPI_EQUALS_MEMBER( sizePoint )
        MXAPI_EQUALS_MEMBER( sizeCss )
        MXAPI_EQUALS_MEMBER( style )
        MXAPI_EQUALS_MEMBER( weight )
        if( ! areVectorsEqual( lhs.fontFamily, rhs.fontFamily ) )
        {
            streamComparisonUnequalMessage( "FontData", "fontFamily" );
            return false;
        }
        MXAPI_EQUALS_MEMBER( underline )
        MXAPI_EQUALS_MEMBER( overline )
        MXAPI_EQUALS_MEMBER( lineThrough )
        MXAPI_EQUALS_END;
        MXAPI_NOT_EQUALS_AND_VECTORS( FontData );
    }
}
