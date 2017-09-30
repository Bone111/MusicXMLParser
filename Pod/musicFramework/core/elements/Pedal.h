// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/PedalAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( PedalAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Pedal )

        inline PedalPtr makePedal() { return std::make_shared<Pedal>(); }

        class Pedal : public ElementInterface
        {
        public:
            Pedal();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            PedalAttributesPtr getAttributes() const;
            void setAttributes( const PedalAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            PedalAttributesPtr myAttributes;
        };
    }
}
