// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/DelayedTurnAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( DelayedTurnAttributes )
        MX_FORWARD_DECLARE_ELEMENT( DelayedTurn )

        inline DelayedTurnPtr makeDelayedTurn() { return std::make_shared<DelayedTurn>(); }

        class DelayedTurn : public ElementInterface
        {
        public:
            DelayedTurn();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            DelayedTurnAttributesPtr getAttributes() const;
            void setAttributes( const DelayedTurnAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            DelayedTurnAttributesPtr myAttributes;
        };
    }
}
