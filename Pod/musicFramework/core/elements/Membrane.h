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

        MX_FORWARD_DECLARE_ELEMENT( Membrane )

        inline MembranePtr makeMembrane() { return std::make_shared<Membrane>(); }
		inline MembranePtr makeMembrane( const MembraneEnum& value ) { return std::make_shared<Membrane>( value ); }
		inline MembranePtr makeMembrane( MembraneEnum&& value ) { return std::make_shared<Membrane>( std::move( value ) ); }

        class Membrane : public ElementInterface
        {
        public:
            Membrane();
            Membrane( const MembraneEnum& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            MembraneEnum getValue() const;
            void setValue( const MembraneEnum& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            MembraneEnum myValue;
        };
    }
}
