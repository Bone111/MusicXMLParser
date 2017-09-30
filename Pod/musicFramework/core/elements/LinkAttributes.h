// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/AttributesInterface.h"
#include "../../core/Decimals.h"
#include "../../core/Enums.h"
#include "../../core/Integers.h"
#include "../../core/Strings.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( LinkAttributes )

        struct LinkAttributes : public AttributesInterface
        {
        public:
            LinkAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            XlinkHref href;
            const XlinkType type;
            XlinkRole role;
            XlinkTitle title;
            XlinkShow show;
            XlinkActuate actuate;
            XsToken name;
            XsNMToken element;
            PositiveInteger position;
            TenthsValue defaultX;
            TenthsValue defaultY;
            TenthsValue relativeX;
            TenthsValue relativeY;
            const bool hasHref;
            bool hasType;
            bool hasRole;
            bool hasTitle;
            bool hasShow;
            bool hasActuate;
            bool hasName;
            bool hasElement;
            bool hasPosition;
            bool hasDefaultX;
            bool hasDefaultY;
            bool hasRelativeX;
            bool hasRelativeY;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
