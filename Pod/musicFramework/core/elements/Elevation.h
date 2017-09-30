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

        MX_FORWARD_DECLARE_ELEMENT( Elevation )

        inline ElevationPtr makeElevation() { return std::make_shared<Elevation>(); }
		inline ElevationPtr makeElevation( const RotationDegrees& value ) { return std::make_shared<Elevation>( value ); }
		inline ElevationPtr makeElevation( RotationDegrees&& value ) { return std::make_shared<Elevation>( std::move( value ) ); }

        class Elevation : public ElementInterface
        {
        public:
            Elevation();
            Elevation( const RotationDegrees& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            RotationDegrees getValue() const;
            void setValue( const RotationDegrees& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            RotationDegrees myValue;
        };
    }
}
