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

        MX_FORWARD_DECLARE_ATTRIBUTES( MultipleRestAttributes )

        struct MultipleRestAttributes : public AttributesInterface
        {
        public:
            MultipleRestAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            YesNo useSymbols;
            bool hasUseSymbols;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
