// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/AttributesInterface.h"
#include "../../core/Enums.h"
#include "../../core/Integers.h"
#include "../../core/Decimals.h"
#include "../../core/Color.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( BracketAttributes )
/*
 <xs:attribute name="type" type="start-stop-continue" use="required"/>
 <xs:attribute name="number" type="number-level"/>
 <xs:attribute name="line-end" type="line-end" use="required"/>
 <xs:attribute name="end-length" type="tenths"/>
 <xs:attributeGroup ref="line-type"/>
 <xs:attributeGroup ref="dashed-formatting"/>
 <xs:attributeGroup ref="position"/>
 <xs:attributeGroup ref="color"/>
 */
        struct BracketAttributes : public AttributesInterface
        {
        public:
            BracketAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            StartStopContinue type;
            NumberLevel number;
            LineEnd lineEnd;
            TenthsValue endLength;
            LineType lineType;
            TenthsValue dashLength;
            TenthsValue spaceLength;
            TenthsValue defaultX;
            TenthsValue defaultY;
            TenthsValue relativeX;
            TenthsValue relativeY;
            Color color;
            const bool hasType;
            bool hasNumber;
            const bool hasLineEnd;
            bool hasEndLength;
            bool hasLineType;
            bool hasDashLength;
            bool hasSpaceLength;
            bool hasDefaultX;
            bool hasDefaultY;
            bool hasRelativeX;
            bool hasRelativeY;
            bool hasColor;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
