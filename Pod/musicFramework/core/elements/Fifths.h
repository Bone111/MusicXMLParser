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

        MX_FORWARD_DECLARE_ELEMENT( Fifths )

        inline FifthsPtr makeFifths() { return std::make_shared<Fifths>(); }
		inline FifthsPtr makeFifths( const FifthsValue& value ) { return std::make_shared<Fifths>( value ); }
		inline FifthsPtr makeFifths( FifthsValue&& value ) { return std::make_shared<Fifths>( std::move( value ) ); }

        class Fifths : public ElementInterface
        {
        public:
            Fifths();
            Fifths( const FifthsValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            FifthsValue getValue() const;
            void setValue( const FifthsValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            FifthsValue myValue;
        };
    }
}
