// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"
#include "../../core/elements/BassStepAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( BassStepAttributes )
        MX_FORWARD_DECLARE_ELEMENT( BassStep )

        inline BassStepPtr makeBassStep() { return std::make_shared<BassStep>(); }
		inline BassStepPtr makeBassStep( const StepEnum& value ) { return std::make_shared<BassStep>( value ); }
		inline BassStepPtr makeBassStep( StepEnum&& value ) { return std::make_shared<BassStep>( std::move( value ) ); }

        class BassStep : public ElementInterface
        {
        public:
            BassStep();
            BassStep( const StepEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            BassStepAttributesPtr getAttributes() const;
            void setAttributes( const BassStepAttributesPtr& attributes );
            StepEnum getValue() const;
            void setValue( const StepEnum& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            StepEnum myValue;
            BassStepAttributesPtr myAttributes;
        };
    }
}
