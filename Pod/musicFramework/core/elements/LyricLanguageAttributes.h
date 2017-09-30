// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/AttributesInterface.h"
#include "../../core/Strings.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( LyricLanguageAttributes )

        struct LyricLanguageAttributes : public AttributesInterface
        {
        public:
            LyricLanguageAttributes();
            virtual bool hasValues() const;
            virtual std::ostream& toStream( std::ostream& os ) const;
            XsNMToken number;
            XsToken name;
            XmlLang lang;
            bool hasNumber;
            bool hasName;
            const bool hasLang;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
