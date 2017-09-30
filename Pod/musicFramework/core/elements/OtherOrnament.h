// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/OtherOrnamentAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( OtherOrnamentAttributes )
        MX_FORWARD_DECLARE_ELEMENT( OtherOrnament )

        inline OtherOrnamentPtr makeOtherOrnament() { return std::make_shared<OtherOrnament>(); }
		inline OtherOrnamentPtr makeOtherOrnament( const XsString& value ) { return std::make_shared<OtherOrnament>( value ); }
		inline OtherOrnamentPtr makeOtherOrnament( XsString&& value ) { return std::make_shared<OtherOrnament>( std::move( value ) ); }

        class OtherOrnament : public ElementInterface
        {
        public:
            OtherOrnament();
            OtherOrnament( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            OtherOrnamentAttributesPtr getAttributes() const;
            void setAttributes( const OtherOrnamentAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            OtherOrnamentAttributesPtr myAttributes;
        };
    }
}
