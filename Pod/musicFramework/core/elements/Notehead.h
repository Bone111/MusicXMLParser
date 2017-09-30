// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"
#include "../../core/elements/NoteheadAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( NoteheadAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Notehead )

        inline NoteheadPtr makeNotehead() { return std::make_shared<Notehead>(); }
		inline NoteheadPtr makeNotehead( const NoteheadValue& value ) { return std::make_shared<Notehead>( value ); }
		inline NoteheadPtr makeNotehead( NoteheadValue&& value ) { return std::make_shared<Notehead>( std::move( value ) ); }

        class Notehead : public ElementInterface
        {
        public:
            Notehead();
            Notehead( const NoteheadValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            NoteheadAttributesPtr getAttributes() const;
            void setAttributes( const NoteheadAttributesPtr& attributes );
            NoteheadValue getValue() const;
            void setValue( const NoteheadValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            NoteheadValue myValue;
            NoteheadAttributesPtr myAttributes;
        };
    }
}
