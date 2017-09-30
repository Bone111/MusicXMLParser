// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/AttributesInterface.h"
#include "../../core/Integers.h"
#include "../../core/Strings.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( BookmarkAttributes )

        struct BookmarkAttributes : public AttributesInterface
        {
        public:
            BookmarkAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            XsID id;
            XsToken name;
            XsNMToken element;
            PositiveInteger position;
            const bool hasId;
            bool hasName;
            bool hasElement;
            bool hasPosition;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
