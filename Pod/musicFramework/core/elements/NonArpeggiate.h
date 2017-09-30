// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/NonArpeggiateAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( NonArpeggiateAttributes )
        MX_FORWARD_DECLARE_ELEMENT( NonArpeggiate )

        inline NonArpeggiatePtr makeNonArpeggiate() { return std::make_shared<NonArpeggiate>(); }

        class NonArpeggiate : public ElementInterface
        {
        public:
            NonArpeggiate();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            NonArpeggiateAttributesPtr getAttributes() const;
            void setAttributes( const NonArpeggiateAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            NonArpeggiateAttributesPtr myAttributes;
        };
    }
}
