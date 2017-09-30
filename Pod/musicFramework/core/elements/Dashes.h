// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/DashesAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( DashesAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Dashes )

        inline DashesPtr makeDashes() { return std::make_shared<Dashes>(); }

        class Dashes : public ElementInterface
        {
        public:
            Dashes();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            DashesAttributesPtr getAttributes() const;
            void setAttributes( const DashesAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            DashesAttributesPtr myAttributes;
        };
    }
}
