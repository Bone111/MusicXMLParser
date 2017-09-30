// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/RehearsalAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( RehearsalAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Rehearsal )

        inline RehearsalPtr makeRehearsal() { return std::make_shared<Rehearsal>(); }
		inline RehearsalPtr makeRehearsal( const XsString& value ) { return std::make_shared<Rehearsal>( value ); }
		inline RehearsalPtr makeRehearsal( XsString&& value ) { return std::make_shared<Rehearsal>( std::move( value ) ); }

        class Rehearsal : public ElementInterface
        {
        public:
            Rehearsal();
            Rehearsal( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            RehearsalAttributesPtr getAttributes() const;
            void setAttributes( const RehearsalAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            RehearsalAttributesPtr myAttributes;
        };
    }
}
