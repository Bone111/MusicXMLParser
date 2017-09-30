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

        MX_FORWARD_DECLARE_ELEMENT( StaffDistance )

        inline StaffDistancePtr makeStaffDistance() { return std::make_shared<StaffDistance>(); }
        inline StaffDistancePtr makeStaffDistance( const TenthsValue& value ) { return std::make_shared<StaffDistance>( value ); }
        inline StaffDistancePtr makeStaffDistance( TenthsValue&& value ) { return std::make_shared<StaffDistance>( std::move( value ) ); }

        class StaffDistance : public ElementInterface
        {
        public:
            StaffDistance();
            StaffDistance( const TenthsValue& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            TenthsValue getValue() const;
            void setValue( const TenthsValue& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            TenthsValue myValue;
        };
    }
}
