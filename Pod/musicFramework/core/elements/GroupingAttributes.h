// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/AttributesInterface.h"
#include "../../core/Enums.h"
#include "../../core/Strings.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( GroupingAttributes )

        struct GroupingAttributes : public AttributesInterface
        {
        public:
            GroupingAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            StartStopSingle type;
            XsToken number;
            XsToken memberOf;
            const 	bool hasType;
            bool hasNumber;
            bool hasMemberOf;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
