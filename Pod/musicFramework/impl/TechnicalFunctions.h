// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/MarkData.h"
#include "../impl/Cursor.h"

#include <memory>
#include <vector>

// TODO - import fingering
// TODO - import pluck
// TODO - import fret
// TODO - import string_
// TODO - import hammerOn
// TODO - import pullOff
// TODO - import bend
// TODO - import tap
// TODO - import hole
// TODO - import arrow
// TODO - import handbell

namespace mx
{
    namespace core
    {
        class TechnicalChoice;
        using TechnicalChoicePtr = std::shared_ptr<TechnicalChoice>;
        using TechnicalChoiceSet = std::vector<TechnicalChoicePtr>;
    }
    
    namespace impl
    {
        class TechnicalFunctions
        {

        public:
            TechnicalFunctions( const core::TechnicalChoiceSet& inTechincalChoiceSet, Cursor inCursor );
            
            void parseTechnicalMarks( std::vector<api::MarkData>& outMarks ) const;
            
        private:
            const core::TechnicalChoiceSet& myTechincalChoiceSet;
            const Cursor myCursor;
            
        private:
            bool parseTechicalMark( const core::TechnicalChoice& techicalChoice, api::MarkData& outMarkData ) const;
        };
    }
}
