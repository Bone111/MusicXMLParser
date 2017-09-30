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

        MX_FORWARD_DECLARE_ELEMENT( TimeRelation )

        inline TimeRelationPtr makeTimeRelation() { return std::make_shared<TimeRelation>(); }
		inline TimeRelationPtr makeTimeRelation( const TimeRelationEnum& value ) { return std::make_shared<TimeRelation>( value ); }
		inline TimeRelationPtr makeTimeRelation( TimeRelationEnum&& value ) { return std::make_shared<TimeRelation>( std::move( value ) ); }

        class TimeRelation : public ElementInterface
        {
        public:
            TimeRelation();
            TimeRelation( const TimeRelationEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            TimeRelationEnum getValue() const;
            void setValue( const TimeRelationEnum& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            TimeRelationEnum myValue;
        };
    }
}
