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

        MX_FORWARD_DECLARE_ELEMENT( MidiBank )

        inline MidiBankPtr makeMidiBank() { return std::make_shared<MidiBank>(); }
		inline MidiBankPtr makeMidiBank( const Midi16384& value ) { return std::make_shared<MidiBank>( value ); }
		inline MidiBankPtr makeMidiBank( Midi16384&& value ) { return std::make_shared<MidiBank>( std::move( value ) ); }

        class MidiBank : public ElementInterface
        {
        public:
            MidiBank();
            MidiBank( const Midi16384& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            Midi16384 getValue() const;
            void setValue( const Midi16384& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            Midi16384 myValue;
        };
    }
}
