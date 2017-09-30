// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/GlissandoAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( GlissandoAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Glissando )

        inline GlissandoPtr makeGlissando() { return std::make_shared<Glissando>(); }
		inline GlissandoPtr makeGlissando( const XsString& value ) { return std::make_shared<Glissando>( value ); }
		inline GlissandoPtr makeGlissando( XsString&& value ) { return std::make_shared<Glissando>( std::move( value ) ); }

        class Glissando : public ElementInterface
        {
        public:
            Glissando();
            Glissando( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            GlissandoAttributesPtr getAttributes() const;
            void setAttributes( const GlissandoAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            GlissandoAttributesPtr myAttributes;
        };
    }
}
