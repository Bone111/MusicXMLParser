// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../api/DurationData.h"

namespace mx
{
    namespace api
    {
        DurationData::DurationData()
        : durationName{ DurationName::unspecified }
        , durationDots{ 0 }
        , durationTimeTicks{ 1 }
        , isTied{ false }
        , timeModificationActualNotes{ 1 }
        , timeModificationNormalNotes{ 1 }
        , timeModificationNormalType{ api::DurationName::unspecified }
        , timeModificationNormalTypeDots{ 0 }
        {
            
        }
    }
}
