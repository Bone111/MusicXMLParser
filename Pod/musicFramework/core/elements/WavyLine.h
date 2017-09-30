// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/WavyLineAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( WavyLineAttributes )
        MX_FORWARD_DECLARE_ELEMENT( WavyLine )

        inline WavyLinePtr makeWavyLine() { return std::make_shared<WavyLine>(); }

        class WavyLine : public ElementInterface
        {
        public:
            WavyLine();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            WavyLineAttributesPtr getAttributes() const;
            void setAttributes( const WavyLineAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            WavyLineAttributesPtr myAttributes;
        };
    }
}
