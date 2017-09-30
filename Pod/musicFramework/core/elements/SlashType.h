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

        MX_FORWARD_DECLARE_ELEMENT( SlashType )

        inline SlashTypePtr makeSlashType() { return std::make_shared<SlashType>(); }
		inline SlashTypePtr makeSlashType( const NoteTypeValue& value ) { return std::make_shared<SlashType>( value ); }
		inline SlashTypePtr makeSlashType( NoteTypeValue&& value ) { return std::make_shared<SlashType>( std::move( value ) ); }

        class SlashType : public ElementInterface
        {
        public:
            SlashType();
            SlashType( const NoteTypeValue& value );

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
