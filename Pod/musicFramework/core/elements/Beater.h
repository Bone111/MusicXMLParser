// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"
#include "../../core/elements/BeaterAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( BeaterAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Beater )

        inline BeaterPtr makeBeater() { return std::make_shared<Beater>(); }
		inline BeaterPtr makeBeater( const BeaterValue& value ) { return std::make_shared<Beater>( value ); }
		inline BeaterPtr makeBeater( BeaterValue&& value ) { return std::make_shared<Beater>( std::move( value ) ); }

        class Beater : public ElementInterface
        {
        public:
            Beater();
            Beater( const BeaterValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            BeaterAttributesPtr getAttributes() const;
            void setAttributes( const BeaterAttributesPtr& attributes );
            BeaterValue getValue() const;
            void setValue( const BeaterValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            BeaterValue myValue;
            BeaterAttributesPtr myAttributes;
        };
    }
}
