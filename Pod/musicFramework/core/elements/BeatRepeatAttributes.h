// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/AttributesInterface.h"
#include "../../core/Enums.h"
#include "../../core/Integers.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( BeatRepeatAttributes )

        struct BeatRepeatAttributes : public AttributesInterface
        {
        public:
            BeatRepeatAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            StartStop type;
            PositiveInteger slashes;
            YesNo useDots;
            const bool hasType;
            bool hasSlashes;
            bool hasUseDots;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
