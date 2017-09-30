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

        MX_FORWARD_DECLARE_ATTRIBUTES( RepeatAttributes )

        struct RepeatAttributes : public AttributesInterface
        {
        public:
            RepeatAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            BackwardForward direction;
            NonNegativeInteger times;
            Winged winged;
            const bool hasDirection;
            bool hasTimes;
            bool hasWinged;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
