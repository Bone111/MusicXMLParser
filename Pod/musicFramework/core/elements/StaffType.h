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

        MX_FORWARD_DECLARE_ELEMENT( StaffType )

        inline StaffTypePtr makeStaffType() { return std::make_shared<StaffType>(); }
		inline StaffTypePtr makeStaffType( const StaffTypeEnum& value ) { return std::make_shared<StaffType>( value ); }
		inline StaffTypePtr makeStaffType( StaffTypeEnum&& value ) { return std::make_shared<StaffType>( std::move( value ) ); }

        class StaffType : public ElementInterface
        {
        public:
            StaffType();
            StaffType( const StaffTypeEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            StaffTypeEnum getValue() const;
            void setValue( const StaffTypeEnum& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            StaffTypeEnum myValue;
        };
    }
}
