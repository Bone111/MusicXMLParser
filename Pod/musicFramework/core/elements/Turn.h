// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/TurnAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( TurnAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Turn )

        inline TurnPtr makeTurn() { return std::make_shared<Turn>(); }

        class Turn : public ElementInterface
        {
        public:
            Turn();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            TurnAttributesPtr getAttributes() const;
            void setAttributes( const TurnAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            TurnAttributesPtr myAttributes;
        };
    }
}
