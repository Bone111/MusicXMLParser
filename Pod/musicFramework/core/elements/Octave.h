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

        MX_FORWARD_DECLARE_ELEMENT( Octave )

        inline OctavePtr makeOctave() { return std::make_shared<Octave>(); }
		inline OctavePtr makeOctave( const OctaveValue& value ) { return std::make_shared<Octave>( value ); }
		inline OctavePtr makeOctave( OctaveValue&& value ) { return std::make_shared<Octave>( std::move( value ) ); }

        class Octave : public ElementInterface
        {
        public:
            Octave();
            Octave( const OctaveValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            OctaveValue getValue() const;
            void setValue( const OctaveValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            OctaveValue myValue;
        };
    }
}
