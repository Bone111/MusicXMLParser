// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/EmptyPrintObjectStyleAlignAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( DampAll )

        inline DampAllPtr makeDampAll() { return std::make_shared<DampAll>(); }

        class DampAll : public ElementInterface
        {
        public:
            DampAll();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            EmptyPrintObjectStyleAlignAttributesPtr getAttributes() const;
            void setAttributes( const EmptyPrintObjectStyleAlignAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            EmptyPrintObjectStyleAlignAttributesPtr myAttributes;
        };
    }
}
