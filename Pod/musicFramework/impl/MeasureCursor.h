// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../impl/Cursor.h"

namespace mx
{
    namespace impl
    {
        class MeasureCursor : public Cursor
        {
        public:
            int partIndex;
            int measureIndex;

            MeasureCursor( int numStaves, int globalTicksPerQuarter )
            : Cursor{ numStaves, globalTicksPerQuarter }
            , partIndex{ 0 }
            , measureIndex{ 0 }
            {
                
            }

        };        
    }
}
