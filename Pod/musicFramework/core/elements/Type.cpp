// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Type.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Type::Type()
        :myValue( NoteTypeValue::quarter )
        ,myAttributes( std::make_shared<TypeAttributes>() )
        {}


        Type::Type( const NoteTypeValue& value )
        :myValue( value )
        ,myAttributes( std::make_shared<TypeAttributes>() )
        {}


        bool Type::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool Type::hasContents() const
        {
            return true;
        }


        std::ostream& Type::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& Type::streamName( std::ostream& os ) const
        {
            os << "type";
            return os;
        }


        std::ostream& Type::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        TypeAttributesPtr Type::getAttributes() const
        {
            return myAttributes;
        }


        void Type::setAttributes( const TypeAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        NoteTypeValue Type::getValue() const
        {
            return myValue;
        }


        void Type::setValue( const NoteTypeValue& value )
        {
            myValue = value;
        }


        bool Type::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            bool isSuccess = true;
            isSuccess &= myAttributes->fromXElement( message, xelement );
            myValue = parseNoteTypeValue( xelement.getValue() );
            MX_RETURN_IS_SUCCESS;
        }

    }
}
