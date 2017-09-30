// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/ToeAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( ToeAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Toe )

        inline ToePtr makeToe() { return std::make_shared<Toe>(); }

        class Toe : public ElementInterface
        {
        public:
            Toe();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            ToeAttributesPtr getAttributes() const;
            void setAttributes( const ToeAttributesPtr& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            ToeAttributesPtr myAttributes;
        };
    }
}
