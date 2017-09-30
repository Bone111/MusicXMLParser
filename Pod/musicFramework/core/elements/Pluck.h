// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/PluckAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( PluckAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Pluck )

        inline PluckPtr makePluck() { return std::make_shared<Pluck>(); }
		inline PluckPtr makePluck( const XsString& value ) { return std::make_shared<Pluck>( value ); }
		inline PluckPtr makePluck( XsString&& value ) { return std::make_shared<Pluck>( std::move( value ) ); }

        class Pluck : public ElementInterface
        {
        public:
            Pluck();
            Pluck( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            PluckAttributesPtr getAttributes() const;
            void setAttributes( const PluckAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            PluckAttributesPtr myAttributes;
        };
    }
}
