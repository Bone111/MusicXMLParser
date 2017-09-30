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

        MX_FORWARD_DECLARE_ELEMENT( NormalType )

        inline NormalTypePtr makeNormalType() { return std::make_shared<NormalType>(); }
		inline NormalTypePtr makeNormalType( const NoteTypeValue& value ) { return std::make_shared<NormalType>( value ); }
		inline NormalTypePtr makeNormalType( NoteTypeValue&& value ) { return std::make_shared<NormalType>( std::move( value ) ); }

        class NormalType : public ElementInterface
        {
        public:
            NormalType();
            NormalType( const NoteTypeValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            NoteTypeValue getValue() const;
            void setValue( const NoteTypeValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            NoteTypeValue myValue;
        };
    }
}
