// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/MeasureData.h"
#include "../impl/MeasureCursor.h"
#include "../api/SystemData.h"
#include "../api/BarlineData.h"
#include "../impl/PropertiesWriter.h"
#include "../impl/Converter.h"

#include <list>

namespace mx
{
	namespace core
	{
		class PartwiseMeasure;
        using PartwiseMeasurePtr = std::shared_ptr<PartwiseMeasure>;
        class Properties;
        using PropertiesPtr = std::shared_ptr<Properties>;
        class Direction;
        using DirectionPtr = std::shared_ptr<Direction>;
	}

    namespace impl
    {
        class ScoreWriter;
        
        class MeasureWriter
        {
		public:
            MeasureWriter( const api::MeasureData& inMeasureData, const MeasureCursor& inCursor, const ScoreWriter& inScoreWriter );
        	core::PartwiseMeasurePtr getPartwiseMeasure();

        private:
            using NoteIter = std::vector<api::NoteData>::const_iterator;
        	const api::MeasureData& myMeasureData;
        	core::PartwiseMeasurePtr myOutMeasure;
            MeasureCursor myCursor;
            MeasureCursor myPreviousCursor;
            const ScoreWriter& myScoreWriter;
            std::unique_ptr<PropertiesWriter> myPropertiesWriter;
            const Converter myConverter;
            std::vector<api::BarlineData>::const_iterator myBarlinesIter;
            std::vector<api::BarlineData>::const_iterator myBarlinesEnd;
            std::vector<api::KeyData>::const_iterator myMeasureKeysIter;
            const std::vector<api::KeyData>::const_iterator myMeasureKeysEnd;
            
        private:
            void writeMeasureGlobals();
            void writeSystemInfo();
            void writeStaves();
            void writeVoices( const api::StaffData& inStaff );
            void writeForwardOrBackupIfNeeded( const api::NoteData& currentNote );
            void backup( const int ticks );
            void forward( const int ticks );
            void advanceCursorIfNeeded( const api::NoteData& currentNote, NoteIter inNoteIter, const NoteIter inEndIter, bool isStartOfChord );
            void writeBarlines( int tickTimePosition );
            
            template<typename T>
            std::vector<T> findItemsAtTimePosition( const std::vector<T>& inItems, int inTickTimePosition )
            {
                std::vector<T> outVector;
                for( const auto& item : inItems )
                {
                    if( item.tickTimePosition == inTickTimePosition )
                    {
                        outVector.push_back( item );
                    }
                }
                return outVector;
            }
        };
    }
}
