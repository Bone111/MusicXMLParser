// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/MarkData.h"
#include "../impl/Cursor.h"

namespace mx
{
    namespace core
    {
        class ArticulationsChoice;
        using ArticulationsChoicePtr = std::shared_ptr<ArticulationsChoice>;
        using ArticulationsChoiceSet = std::vector<ArticulationsChoicePtr>;
    }
    
    namespace impl
    {
        class ArticulationsFunctions
        {
        public:
            ArticulationsFunctions( const core::ArticulationsChoiceSet& inArticulations, impl::Cursor inCursor );
            ~ArticulationsFunctions() = default;
            ArticulationsFunctions( const ArticulationsFunctions& ) = delete;
            ArticulationsFunctions( ArticulationsFunctions&& ) = delete;
            ArticulationsFunctions& operator=( const ArticulationsFunctions& ) = delete;
            ArticulationsFunctions& operator=( ArticulationsFunctions&& ) = delete;
            
            void parseArticulations( std::vector<api::MarkData>& outMarks ) const;
            
        private:
            const core::ArticulationsChoiceSet& myArticulations;
            const impl::Cursor myCursor;
            
        private:
            void parseArticulation( const core::ArticulationsChoice& inArticulation, api::MarkData& outMark ) const;
        };
    }
}
