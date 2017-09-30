// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/StringMuteAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( StringMuteAttributes )
        MX_FORWARD_DECLARE_ELEMENT( StringMute )

        inline StringMutePtr makeStringMute() { return std::make_shared<StringMute>(); }

        class StringMute : public ElementInterface
        {
        public:
            StringMute();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            StringMuteAttributesPtr getAttributes() const;
            void setAttributes( const StringMuteAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            StringMuteAttributesPtr myAttributes;
        };
    }
}
