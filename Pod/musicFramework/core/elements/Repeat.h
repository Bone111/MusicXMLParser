// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/RepeatAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( RepeatAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Repeat )

        inline RepeatPtr makeRepeat() { return std::make_shared<Repeat>(); }

        class Repeat : public ElementInterface
        {
        public:
            Repeat();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            RepeatAttributesPtr getAttributes() const;
            void setAttributes( const RepeatAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            RepeatAttributesPtr myAttributes;
        };
    }
}
