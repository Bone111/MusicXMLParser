// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/ApiCommon.h"

#include <string>
#include <vector>

namespace mx
{
    namespace api
    {
        
        // distance values are in 'tenths' governed by the 'scaling' values

        class LayoutData
        {
        public:

            long double scalingMillimeters;
            long double scalingTenths;

            inline long double tenthsPerMillimeter() const
            {
                return scalingTenths / scalingMillimeters;
            }

            inline long double tenthsPerInch() const
            {
                return tenthsPerMillimeter() * 25.4;
            }

            long double pageWidth;             // negative number represent the absence of a value
            long double pageHeight;            // negative number represent the absence of a value

            long double oddPageLeftMargin;     // negative number represent the absence of a value
            long double oddPageRightMargin;    // negative number represent the absence of a value
            long double oddPageTopMargin;      // negative number represent the absence of a value
            long double oddPageBottomMargin;   // negative number represent the absence of a value
            long double evenPageLeftMargin;    // negative number represent the absence of a value
            long double evenPageRightMargin;   // negative number represent the absence of a value
            long double evenPageTopMargin;     // negative number represent the absence of a value
            long double evenPageBottomMargin;  // negative number represent the absence of a value

            long double systemLeftMargin;      // negative number represent the absence of a value
            long double systemRightMargin;     // negative number represent the absence of a value
            long double systemDistance;        // distance from bollom line of one system to top line of next system, negative number represent the absence of a value
            long double topSystemDistance;     // first system distance from top margin to top line of first staff, negative number represent the absence of a value
            long double staffDistance;         // the space between staves within the same system, negative number represent the absence of a value
            
            MeasureNumbering measureNumbering; // measure numbering setting at the global level, will be stated in first measure's <print> tag.  can be overridden by a value in the Measure
            
            LayoutData()
            : scalingMillimeters( -1.0 )
            , scalingTenths( -1.0 )
            , pageWidth( -1.0 )
            , pageHeight( -1.0 )
            , oddPageLeftMargin( -1.0 )
            , oddPageRightMargin( -1.0 )
            , oddPageTopMargin( -1.0 )
            , oddPageBottomMargin( -1.0 )
            , evenPageLeftMargin( -1.0 )
            , evenPageRightMargin( -1.0 )
            , evenPageTopMargin( -1.0 )
            , evenPageBottomMargin( -1.0 )
            , systemLeftMargin( -1.0 )
            , systemRightMargin( -1.0 )
            , systemDistance( -1.0 )
            , topSystemDistance( -1.0 )
            , staffDistance( -1.0 )
            , measureNumbering{ MeasureNumbering::unspecified }
            {

            }


            inline bool areOddMarginsValid() const
            {
                return oddPageLeftMargin > 0
                    && oddPageRightMargin > 0
                    && oddPageTopMargin > 0
                    && oddPageBottomMargin > 0;
            }


            inline bool areEvenMarginsValid() const
            {
                return evenPageLeftMargin > 0
                    && evenPageRightMargin > 0
                    && evenPageTopMargin > 0
                    && evenPageBottomMargin > 0;
            }


            inline bool areOddEvenMarginsTheSame() const
            {
                return areSame(oddPageLeftMargin, evenPageLeftMargin)
                    && areSame(oddPageRightMargin, evenPageRightMargin)
                    && areSame(oddPageTopMargin, evenPageTopMargin)
                    && areSame(oddPageBottomMargin, evenPageBottomMargin);
            }

        };
        
        MXAPI_EQUALS_BEGIN( LayoutData )
        MXAPI_EQUALS_MEMBER( pageWidth )
        MXAPI_EQUALS_MEMBER( pageHeight )
        MXAPI_EQUALS_MEMBER( oddPageLeftMargin )
        MXAPI_EQUALS_MEMBER( oddPageRightMargin )
        MXAPI_EQUALS_MEMBER( oddPageTopMargin )
        MXAPI_EQUALS_MEMBER( oddPageBottomMargin )
        MXAPI_EQUALS_MEMBER( evenPageLeftMargin )
        MXAPI_EQUALS_MEMBER( evenPageRightMargin )
        MXAPI_EQUALS_MEMBER( evenPageTopMargin )
        MXAPI_EQUALS_MEMBER( evenPageBottomMargin )
        MXAPI_EQUALS_MEMBER( systemLeftMargin )
        MXAPI_EQUALS_MEMBER( systemRightMargin )
        MXAPI_EQUALS_MEMBER( systemDistance )
        MXAPI_EQUALS_MEMBER( topSystemDistance )
        MXAPI_EQUALS_MEMBER( staffDistance )
        MXAPI_EQUALS_MEMBER( measureNumbering )
        MXAPI_EQUALS_END;
        MXAPI_NOT_EQUALS_AND_VECTORS( LayoutData );
    }
}
