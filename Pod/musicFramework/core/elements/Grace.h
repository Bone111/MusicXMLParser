// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/GraceAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( GraceAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Grace )

        inline GracePtr makeGrace() { return std::make_shared<Grace>(); }

        class Grace : public ElementInterface
        {
        public:
            Grace();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            GraceAttributesPtr getAttributes() const;
            void setAttributes( const GraceAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            GraceAttributesPtr myAttributes;
        };
    }
}
