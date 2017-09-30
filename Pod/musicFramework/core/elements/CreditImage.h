// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/CreditImageAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( CreditImageAttributes )
        MX_FORWARD_DECLARE_ELEMENT( CreditImage )

        inline CreditImagePtr makeCreditImage() { return std::make_shared<CreditImage>(); }

        class CreditImage : public ElementInterface
        {
        public:
            CreditImage();

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            CreditImageAttributesPtr getAttributes() const;
            void setAttributes( const CreditImageAttributesPtr& attributes );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            CreditImageAttributesPtr myAttributes;
        };
    }
}
