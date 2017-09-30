// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/LyricLanguageAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( LyricLanguageAttributes )
        MX_FORWARD_DECLARE_ELEMENT( LyricLanguage )

        inline LyricLanguagePtr makeLyricLanguage() { return std::make_shared<LyricLanguage>(); }

        class LyricLanguage : public ElementInterface
        {
        public:
            LyricLanguage();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            LyricLanguageAttributesPtr getAttributes() const;
            void setAttributes( const LyricLanguageAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            LyricLanguageAttributesPtr myAttributes;
        };
    }
}
