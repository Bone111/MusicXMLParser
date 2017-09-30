// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/WordsAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( WordsAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Words )

        inline WordsPtr makeWords() { return std::make_shared<Words>(); }
		inline WordsPtr makeWords( const XsString& value ) { return std::make_shared<Words>( value ); }
		inline WordsPtr makeWords( XsString&& value ) { return std::make_shared<Words>( std::move( value ) ); }

        class Words : public ElementInterface
        {
        public:
            Words();
            Words( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            WordsAttributesPtr getAttributes() const;
            void setAttributes( const WordsAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            WordsAttributesPtr myAttributes;
        };
    }
}
