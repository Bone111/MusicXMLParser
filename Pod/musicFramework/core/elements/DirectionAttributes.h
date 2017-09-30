// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/AttributesInterface.h"
#include "../../core/Enums.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( DirectionAttributes )

        struct DirectionAttributes : public AttributesInterface
        {
        public:
            DirectionAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            AboveBelow placement;
            YesNo directive;
            bool hasPlacement;
            bool hasDirective;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
