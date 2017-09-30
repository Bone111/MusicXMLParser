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

        MX_FORWARD_DECLARE_ELEMENT( InstrumentSound )

        inline InstrumentSoundPtr makeInstrumentSound() { return std::make_shared<InstrumentSound>(); }
		inline InstrumentSoundPtr makeInstrumentSound( const XsString& value ) { return std::make_shared<InstrumentSound>( value ); }
		inline InstrumentSoundPtr makeInstrumentSound( XsString&& value ) { return std::make_shared<InstrumentSound>( std::move( value ) ); }

        class InstrumentSound : public ElementInterface
        {
        public:
            InstrumentSound();
            InstrumentSound( const XsString& value );

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
