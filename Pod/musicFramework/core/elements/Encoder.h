// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/EncoderAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( EncoderAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Encoder )

        inline EncoderPtr makeEncoder() { return std::make_shared<Encoder>(); }
		inline EncoderPtr makeEncoder( const XsString& value ) { return std::make_shared<Encoder>( value ); }
		inline EncoderPtr makeEncoder( XsString&& value ) { return std::make_shared<Encoder>( std::move( value ) ); }

        class Encoder : public ElementInterface
        {
        public:
            Encoder();
            Encoder( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            EncoderAttributesPtr getAttributes() const;
            void setAttributes( const EncoderAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            EncoderAttributesPtr myAttributes;
        };
    }
}
