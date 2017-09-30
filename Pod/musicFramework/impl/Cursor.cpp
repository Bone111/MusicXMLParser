// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../impl/Cursor.h"
#include "../core/elements/Duration.h"

namespace mx
{
    namespace impl
    {
        Cursor::Cursor( int numStaves, int globalTicksPerQuarter )
        : timeSignature{}
        , ticksPerQuarter( globalTicksPerQuarter )
        , tickTimePosition( 0 )
        , voiceIndex( 0 )
        , staffIndex( 0 )
        , isBackupInProgress( false )
        , isFirstMeasureInPart( true )
        , isChordActive( false )
        , myNumStaves( numStaves )
        , myGlobalTicksPerQuarter( globalTicksPerQuarter )
        {
            
        }


        int Cursor::getNumStaves() const
        {
            return myNumStaves;
        }


        int Cursor::getGlobalTicksPerQuarter() const
        {
            return myGlobalTicksPerQuarter;
        }
        

        void Cursor::reset()
        {
            tickTimePosition = 0;
            staffIndex = 0;
            voiceIndex = 0;
            isBackupInProgress = false;
            isChordActive = false;
        }


        int Cursor::convertDurationToGlobalTickScale( const core::Duration& duration ) const
        {
            return convertDurationToGlobalTickScale( static_cast<long double>( duration.getValue().getValue() ) );
        }


        int Cursor::convertDurationToGlobalTickScale( long double durationValue ) const
        {
            if( this->ticksPerQuarter == this->getGlobalTicksPerQuarter() )
            {
                return static_cast<int>( std::ceil( durationValue - 0.5L ) );
            }
            
            const long double currentTicksPerQuarter = static_cast<long double>( this->ticksPerQuarter );
            const long double globalTicksPerQuarter = static_cast<long double>( this->getGlobalTicksPerQuarter() );
            const long double convertedVal = durationValue * ( globalTicksPerQuarter / currentTicksPerQuarter );
            return static_cast<int>( std::ceil( convertedVal - 0.5L ) );
        }


        int Cursor::convertDurationToGlobalTickScale( int durationValue ) const
        {
            return convertDurationToGlobalTickScale( static_cast<long double>( durationValue ) );
        }
    }
}
