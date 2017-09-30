// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/MordentAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( MordentAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Mordent )

        inline MordentPtr makeMordent() { return std::make_shared<Mordent>(); }

        class Mordent : public ElementInterface
        {
        public:
            Mordent();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            MordentAttributesPtr getAttributes() const;
            void setAttributes( const MordentAttributesPtr& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            MordentAttributesPtr myAttributes;
        };
    }
}
