// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/MeasureData.h"
#include "../api/TimeSignatureData.h"
#include "../core/elements/PartwiseMeasure.h"

namespace mx
{
    namespace core
    {
        class Duration;
    }

    namespace impl
    {
        class Cursor
        {
        public:

            api::TimeSignatureData timeSignature;
            int ticksPerQuarter;
            int tickTimePosition;
            int voiceIndex;
            int staffIndex;
            bool isBackupInProgress;
            bool isFirstMeasureInPart;
            
            bool isChordActive;

            Cursor( int numStaves, int globalTicksPerQuarter );
            virtual ~Cursor() = default;
            Cursor( const Cursor& ) = default;
            Cursor( Cursor&& ) = default;
            Cursor& operator=( const Cursor& ) = default;
            Cursor& operator=( Cursor&& ) = default;
            
            int getNumStaves() const;
            int getGlobalTicksPerQuarter() const;

			// use this to clear the state
			// when starting a new measure     
            void reset();

            int convertDurationToGlobalTickScale( const core::Duration& duration ) const;
            int convertDurationToGlobalTickScale( long double durationValue ) const;
            int convertDurationToGlobalTickScale( int duration ) const;

        private:
            int myNumStaves;
            int myGlobalTicksPerQuarter;
        };        
    }
}
