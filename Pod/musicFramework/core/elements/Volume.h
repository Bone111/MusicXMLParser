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

        MX_FORWARD_DECLARE_ELEMENT( Volume )

        inline VolumePtr makeVolume() { return std::make_shared<Volume>(); }
		inline VolumePtr makeVolume( const Percent& value ) { return std::make_shared<Volume>( value ); }
		inline VolumePtr makeVolume( Percent&& value ) { return std::make_shared<Volume>( std::move( value ) ); }

        class Volume : public ElementInterface
        {
        public:
            Volume();
            Volume( const Percent& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            Percent getValue() const;
            void setValue( const Percent& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            Percent myValue;
        };
    }
}
