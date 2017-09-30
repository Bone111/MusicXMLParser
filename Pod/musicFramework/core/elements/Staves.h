// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Integers.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( Staves )

        inline StavesPtr makeStaves() { return std::make_shared<Staves>(); }
		inline StavesPtr makeStaves( const NonNegativeInteger& value ) { return std::make_shared<Staves>( value ); }
		inline StavesPtr makeStaves( NonNegativeInteger&& value ) { return std::make_shared<Staves>( std::move( value ) ); }

        class Staves : public ElementInterface
        {
        public:
            Staves();
            Staves( const NonNegativeInteger& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            NonNegativeInteger getValue() const;
            void setValue( const NonNegativeInteger& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            NonNegativeInteger myValue;
        };
    }
}
