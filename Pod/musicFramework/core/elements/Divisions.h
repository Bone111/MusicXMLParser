// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Decimals.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( Divisions )

        inline DivisionsPtr makeDivisions() { return std::make_shared<Divisions>(); }
		inline DivisionsPtr makeDivisions( const PositiveDivisionsValue& value ) { return std::make_shared<Divisions>( value ); }
		inline DivisionsPtr makeDivisions( PositiveDivisionsValue&& value ) { return std::make_shared<Divisions>( std::move( value ) ); }

        class Divisions : public ElementInterface
        {
        public:
            Divisions();
            Divisions( const PositiveDivisionsValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            PositiveDivisionsValue getValue() const;
            void setValue( const PositiveDivisionsValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            PositiveDivisionsValue myValue;
        };
    }
}
