// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../api/MarkData.h"
#include "../impl/Converter.h"
#include "../impl/Cursor.h"

namespace mx
{
    namespace core
    {
        class AccidentalMark;
    }
    
    namespace impl
    {
        class AccidentalMarkFunctions
        {
        public:
            AccidentalMarkFunctions( const core::AccidentalMark& inAccidentalMark, impl::Cursor inCursor );
            ~AccidentalMarkFunctions() = default;
            AccidentalMarkFunctions( const AccidentalMarkFunctions& ) = default;
            AccidentalMarkFunctions( AccidentalMarkFunctions&& ) = default;
            AccidentalMarkFunctions& operator=( const AccidentalMarkFunctions& ) = default;
            AccidentalMarkFunctions& operator=( AccidentalMarkFunctions&& ) = default;
            
            api::MarkData parseAccidentalMark() const;
            
        private:
            const core::AccidentalMark& myAccidentalMark;
            const impl::Cursor myCursor;
        };
    }
}
