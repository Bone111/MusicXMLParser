// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/AttributesInterface.h"
#include "../../core/Decimals.h"
#include "../../core/Enums.h"
#include "../../core/Integers.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( WavyLineAttributes )

        struct WavyLineAttributes : public AttributesInterface
        {
        public:
            WavyLineAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            StartStopContinue type;
            NumberLevel number;
            TenthsValue defaultX;
            TenthsValue defaultY;
            TenthsValue relativeX;
            TenthsValue relativeY;
            AboveBelow placement;
            StartNote startNote;
            TrillStep trillStep;
            TwoNoteTurn twoNoteTurn;
            YesNo accelerate;
            TrillBeats beats;
            Percent secondBeat;
            Percent lastBeat;
            const bool hasType;
            bool hasNumber;
            bool hasDefaultX;
            bool hasDefaultY;
            bool hasRelativeX;
            bool hasRelativeY;
            bool hasPlacement;
            bool hasStartNote;
            bool hasTrillStep;
            bool hasTwoNoteTurn;
            bool hasAccelerate;
            bool hasBeats;
            bool hasSecondBeat;
            bool hasLastBeat;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
