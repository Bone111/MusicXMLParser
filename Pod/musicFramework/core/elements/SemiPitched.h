// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( SemiPitched )

        inline SemiPitchedPtr makeSemiPitched() { return std::make_shared<SemiPitched>(); }
		inline SemiPitchedPtr makeSemiPitched( const SemiPitchedEnum& value ) { return std::make_shared<SemiPitched>( value ); }
		inline SemiPitchedPtr makeSemiPitched( SemiPitchedEnum&& value ) { return std::make_shared<SemiPitched>( std::move( value ) ); }

        class SemiPitched : public ElementInterface
        {
        public:
            SemiPitched();
            SemiPitched( const SemiPitchedEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            SemiPitchedEnum getValue() const;
            void setValue( const SemiPitchedEnum& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            SemiPitchedEnum myValue;
        };
    }
}
