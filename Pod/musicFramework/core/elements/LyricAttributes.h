// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/AttributesInterface.h"
#include "../../core/Decimals.h"
#include "../../core/Enums.h"
#include "../../core/Strings.h"
#include "../../core/Color.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( LyricAttributes )

        struct LyricAttributes : public AttributesInterface
        {
        public:
            LyricAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            XsNMToken number;
            XsToken name;
            LeftCenterRight justify;
            TenthsValue defaultX;
            TenthsValue defaultY;
            TenthsValue relativeX;
            TenthsValue relativeY;
            AboveBelow placement;
            Color color;
            YesNo printObject;
            bool hasNumber;
            bool hasName;
            bool hasJustify;
            bool hasDefaultX;
            bool hasDefaultY;
            bool hasRelativeX;
            bool hasRelativeY;
            bool hasPlacement;
            bool hasColor;
            bool hasPrintObject;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
