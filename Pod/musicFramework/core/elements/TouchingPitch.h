// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( TouchingPitch )

        inline TouchingPitchPtr makeTouchingPitch() { return std::make_shared<TouchingPitch>(); }

        class TouchingPitch : public ElementInterface
        {
        public:
            TouchingPitch();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            
            bool fromXElement( std::ostream& message, xml::XElement& xelement );
        };
    }
}
