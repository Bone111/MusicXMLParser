// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/AccordionRegistrationAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( AccordionRegistrationAttributes )
        MX_FORWARD_DECLARE_ELEMENT( AccordionHigh )
        MX_FORWARD_DECLARE_ELEMENT( AccordionLow )
        MX_FORWARD_DECLARE_ELEMENT( AccordionMiddle )
        MX_FORWARD_DECLARE_ELEMENT( AccordionRegistration )

        inline AccordionRegistrationPtr makeAccordionRegistration() { return std::make_shared<AccordionRegistration>(); }

        class AccordionRegistration : public ElementInterface
        {
        public:
            AccordionRegistration();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            AccordionRegistrationAttributesPtr getAttributes() const;
            void setAttributes( const AccordionRegistrationAttributesPtr& value );

            /* _________ AccordionHigh minOccurs = 0, maxOccurs = 1 _________ */
            AccordionHighPtr getAccordionHigh() const;
            void setAccordionHigh( const AccordionHighPtr& value );
            bool getHasAccordionHigh() const;
            void setHasAccordionHigh( const bool value );

            /* _________ AccordionMiddle minOccurs = 0, maxOccurs = 1 _________ */
            AccordionMiddlePtr getAccordionMiddle() const;
            void setAccordionMiddle( const AccordionMiddlePtr& value );
            bool getHasAccordionMiddle() const;
            void setHasAccordionMiddle( const bool value );

            /* _________ AccordionLow minOccurs = 0, maxOccurs = 1 _________ */
            AccordionLowPtr getAccordionLow() const;
            void setAccordionLow( const AccordionLowPtr& value );
            bool getHasAccordionLow() const;
            void setHasAccordionLow( const bool value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            AccordionRegistrationAttributesPtr myAttributes;
            AccordionHighPtr myAccordionHigh;
            bool myHasAccordionHigh;
            AccordionMiddlePtr myAccordionMiddle;
            bool myHasAccordionMiddle;
            AccordionLowPtr myAccordionLow;
            bool myHasAccordionLow;
        };
    }
}
