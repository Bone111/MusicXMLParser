// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../xml/XDoc.h"
#include <memory>

namespace mx
{
    namespace xml
    {
        class XFactory
        {
        public:
            static XDocPtr makeXDoc();
            static XElementPtr makeXElement();
        };
    }
}
