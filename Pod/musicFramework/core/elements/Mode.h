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

        MX_FORWARD_DECLARE_ELEMENT( Mode )

        inline ModePtr makeMode() { return std::make_shared<Mode>(); }
		inline ModePtr makeMode( const ModeValue& value ) { return std::make_shared<Mode>( value ); }
		inline ModePtr makeMode( ModeValue&& value ) { return std::make_shared<Mode>( std::move( value ) ); }

        class Mode : public ElementInterface
        {
        public:
            Mode();
            Mode( const ModeValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            ModeValue getValue() const;
            void setValue( const ModeValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            ModeValue myValue;
        };
    }
}
