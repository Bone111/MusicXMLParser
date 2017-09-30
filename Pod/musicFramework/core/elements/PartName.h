// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/PartNameAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( PartNameAttributes )
        MX_FORWARD_DECLARE_ELEMENT( PartName )

        inline PartNamePtr makePartName() { return std::make_shared<PartName>(); }
		inline PartNamePtr makePartName( const XsString& value ) { return std::make_shared<PartName>( value ); }
		inline PartNamePtr makePartName( XsString&& value ) { return std::make_shared<PartName>( std::move( value ) ); }

        class PartName : public ElementInterface
        {
        public:
            PartName();
            PartName( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            PartNameAttributesPtr getAttributes() const;
            void setAttributes( const PartNameAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            PartNameAttributesPtr myAttributes;
        };
    }
}
