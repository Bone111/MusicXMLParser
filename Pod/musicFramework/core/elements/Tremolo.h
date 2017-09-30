// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Integers.h"
#include "../../core/elements/TremoloAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( TremoloAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Tremolo )

        inline TremoloPtr makeTremolo() { return std::make_shared<Tremolo>(); }
		inline TremoloPtr makeTremolo( const TremoloMarks& value ) { return std::make_shared<Tremolo>( value ); }
		inline TremoloPtr makeTremolo( TremoloMarks&& value ) { return std::make_shared<Tremolo>( std::move( value ) ); }

        class Tremolo : public ElementInterface
        {
        public:
            Tremolo();
            Tremolo( const TremoloMarks& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            TremoloAttributesPtr getAttributes() const;
            void setAttributes( const TremoloAttributesPtr& attributes );
            TremoloMarks getValue() const;
            void setValue( const TremoloMarks& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            TremoloMarks myValue;
            TremoloAttributesPtr myAttributes;
        };
    }
}
