// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/StaffData.h"
#include "../api/TimeSignatureData.h"
#include "../api/ClefData.h"
#include "../api/TempoData.h"
#include "../api/DirectionData.h"
#include "../api/KeyData.h"
#include "../api/BarlineData.h"

#include <string>
#include <map>

namespace mx
{
    namespace api
    {
        class MeasureData
        {
        public:
            
            // this is the notes and other music data
            std::vector<StaffData> staves;
            
            TimeSignatureData timeSignature;

            // an empty measureNumber indicates a normal
            // measure number (i.e. the measure's
            // index + 1).  only read or write to
            // this field when handling overridden
            // measure numbers
            //
            // MusicXML Documentation:
            // In partwise files, the number attribute
            // should be the same for measures in
            // different parts that share the same left
            // barline. While the number attribute is
            // often numeric, it does not have to be.
            // Non-numeric values are typically used
            // together with the implicit or non-
            // controlling attributes being set to "yes".
            // For a pickup measure, the number attribute
            // is typically set to "0" and the implicit
            // attribute is typically set to "yes".
            // Further details about measure numbering
            // can be defined using the measure-numbering
            // element.
            std::string number;

            // The measure-numbering-value type
            // describes how measure numbers are
            // displayed on this part: no numbers,
            // numbers every measure, or numbers
            // every system.
            //
            MeasureNumbering measureNumbering;
            
            // a number greater than zero indicates that
            // this measure is the beginning of a mult-
            // measure rest that will last for the
            // indicated number of measures. following
            // measures will be affected by this.
            int multiMeasureRest;
            
            // The implicit attribute is set to "yes" for
            // measures where the measure number should
            // never appear, such as pickup measures and
            // the last half of mid-measure repeats. The
            // value is "no" if not specified.
            Bool implicit;
            
            // The non-controlling attribute is intended for
            // use in multimetric music like the Don Giovanni
            // minuet. If set to "yes", the left barline in
            // this measure does not coincide with the left
            // barline of measures in other parts. The value
            // is "no" if not specified.
            Bool nonControlling;
            
            // a width value less than 0 means 'unspecified'
            long double width;
            std::vector<KeyData> keys;
            std::vector<BarlineData> barlines;

            MeasureData()
            : staves{}
            , timeSignature{}
            , number{}
            , measureNumbering{ MeasureNumbering::unspecified }
            , multiMeasureRest{ -1 }
            , implicit{ Bool::unspecified }
            , nonControlling{ Bool::unspecified }
            , width{ -1.0 }
            {
                
            }
        };
        
        MXAPI_EQUALS_BEGIN( MeasureData )
        MXAPI_EQUALS_MEMBER( staves )
        MXAPI_EQUALS_MEMBER( timeSignature )
        MXAPI_EQUALS_MEMBER( number )
        MXAPI_EQUALS_MEMBER( measureNumbering )
        MXAPI_EQUALS_MEMBER( multiMeasureRest )
        MXAPI_EQUALS_MEMBER( implicit )
        MXAPI_EQUALS_MEMBER( nonControlling )
        MXAPI_EQUALS_MEMBER( width )
        MXAPI_EQUALS_MEMBER( keys )
        MXAPI_EQUALS_MEMBER( barlines )
        MXAPI_EQUALS_END;
        MXAPI_NOT_EQUALS_AND_VECTORS( MeasureData );
    }
}
