// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Enums.h"
#include "../../core/elements/TypeAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( TypeAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Type )

        inline TypePtr makeType() { return std::make_shared<Type>(); }
		inline TypePtr makeType( const NoteTypeValue& value ) { return std::make_shared<Type>( value ); }
		inline TypePtr makeType( NoteTypeValue&& value ) { return std::make_shared<Type>( std::move( value ) ); }

        class Type : public ElementInterface
        {
        public:
            Type();
            Type( const NoteTypeValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            TypeAttributesPtr getAttributes() const;
            void setAttributes( const TypeAttributesPtr& attributes );
            NoteTypeValue getValue() const;
            void setValue( const NoteTypeValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            NoteTypeValue myValue;
            TypeAttributesPtr myAttributes;
        };
    }
}
