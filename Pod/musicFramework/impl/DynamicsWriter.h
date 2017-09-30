// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/MarkData.h"
#include "../impl/Cursor.h"
#include "../impl/Converter.h"

namespace mx
{
    namespace core
    {
        class Dynamics;
        using DynamicsPtr = std::shared_ptr<Dynamics>;
        using DynamicsSet = std::vector<DynamicsPtr>;
    }
    
    namespace impl
    {
        class DynamicsWriter
        {
        public:
            DynamicsWriter( const api::MarkData& inMark, impl::Cursor inCursor );            
            DynamicsWriter( const api::MarkData& inMark, impl::Cursor inCursor, api::Placement directionPlacement );
            core::DynamicsPtr getDynamics() const;
            
        private:
            const api::MarkData& myMarkData;
            const impl::Cursor myCursor;
            const api::Placement myDirectionPlacement;
            const Converter myConverter;
            
        private:
            
        };
    }
}
