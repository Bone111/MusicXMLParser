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

        MX_FORWARD_DECLARE_ELEMENT( WorkNumber )

        inline WorkNumberPtr makeWorkNumber() { return std::make_shared<WorkNumber>(); }
		inline WorkNumberPtr makeWorkNumber( const XsString& value ) { return std::make_shared<WorkNumber>( value ); }
		inline WorkNumberPtr makeWorkNumber( XsString&& value ) { return std::make_shared<WorkNumber>( std::move( value ) ); }

        class WorkNumber : public ElementInterface
        {
        public:
            WorkNumber();
            WorkNumber( const XsString& value );

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
