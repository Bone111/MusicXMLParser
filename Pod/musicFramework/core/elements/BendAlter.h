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

        MX_FORWARD_DECLARE_ELEMENT( BendAlter )

        inline BendAlterPtr makeBendAlter() { return std::make_shared<BendAlter>(); }
		inline BendAlterPtr makeBendAlter( const Semitones& value ) { return std::make_shared<BendAlter>( value ); }
		inline BendAlterPtr makeBendAlter( Semitones&& value ) { return std::make_shared<BendAlter>( std::move( value ) ); }

        class BendAlter : public ElementInterface
        {
        public:
            BendAlter();
            BendAlter( const Semitones& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            Semitones getValue() const;
            void setValue( const Semitones& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            Semitones myValue;
        };
    }
}
