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

        MX_FORWARD_DECLARE_ELEMENT( StickType )

        inline StickTypePtr makeStickType() { return std::make_shared<StickType>(); }
		inline StickTypePtr makeStickType( const StickTypeEnum& value ) { return std::make_shared<StickType>( value ); }
		inline StickTypePtr makeStickType( StickTypeEnum&& value ) { return std::make_shared<StickType>( std::move( value ) ); }

        class StickType : public ElementInterface
        {
        public:
            StickType();
            StickType( const StickTypeEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            StickTypeEnum getValue() const;
            void setValue( const StickTypeEnum& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            StickTypeEnum myValue;
        };
    }
}
