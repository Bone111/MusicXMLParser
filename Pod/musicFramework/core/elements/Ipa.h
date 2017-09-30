// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( Ipa )

        inline IpaPtr makeIpa() { return std::make_shared<Ipa>(); }
		inline IpaPtr makeIpa( const XsString& value ) { return std::make_shared<Ipa>( value ); }
		inline IpaPtr makeIpa( XsString&& value ) { return std::make_shared<Ipa>( std::move( value ) ); }

        class Ipa : public ElementInterface
        {
        public:
            Ipa();
            Ipa( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
        };
    }
}
