// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Decimals.h"
#include "../../core/elements/NoteSizeAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( NoteSizeAttributes )
        MX_FORWARD_DECLARE_ELEMENT( NoteSize )

        inline NoteSizePtr makeNoteSize() { return std::make_shared<NoteSize>(); }
		inline NoteSizePtr makeNoteSize( const NonNegativeDecimal& value ) { return std::make_shared<NoteSize>( value ); }
		inline NoteSizePtr makeNoteSize( NonNegativeDecimal&& value ) { return std::make_shared<NoteSize>( std::move( value ) ); }

        class NoteSize : public ElementInterface
        {
        public:
            NoteSize();
            NoteSize( const NonNegativeDecimal& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            NoteSizeAttributesPtr getAttributes() const;
            void setAttributes( const NoteSizeAttributesPtr& attributes );
            NonNegativeDecimal getValue() const;
            void setValue( const NonNegativeDecimal& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            NonNegativeDecimal myValue;
            NoteSizeAttributesPtr myAttributes;
        };
    }
}
