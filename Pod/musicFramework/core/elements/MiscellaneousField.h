// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/MiscellaneousFieldAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( MiscellaneousFieldAttributes )
        MX_FORWARD_DECLARE_ELEMENT( MiscellaneousField )

        inline MiscellaneousFieldPtr makeMiscellaneousField() { return std::make_shared<MiscellaneousField>(); }
		inline MiscellaneousFieldPtr makeMiscellaneousField( const XsString& value ) { return std::make_shared<MiscellaneousField>( value ); }
		inline MiscellaneousFieldPtr makeMiscellaneousField( XsString&& value ) { return std::make_shared<MiscellaneousField>( std::move( value ) ); }

        class MiscellaneousField : public ElementInterface
        {
        public:
            MiscellaneousField();
            MiscellaneousField( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            MiscellaneousFieldAttributesPtr getAttributes() const;
            void setAttributes( const MiscellaneousFieldAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            MiscellaneousFieldAttributesPtr myAttributes;
        };
    }
}
