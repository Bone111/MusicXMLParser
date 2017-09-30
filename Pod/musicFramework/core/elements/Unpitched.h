// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ELEMENT( DisplayStepOctaveGroup )
        MX_FORWARD_DECLARE_ELEMENT( Unpitched )

        inline UnpitchedPtr makeUnpitched() { return std::make_shared<Unpitched>(); }

        class Unpitched : public ElementInterface
        {
        public:
            Unpitched();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;

            /* _________ DisplayStepOctaveGroup minOccurs = 0, maxOccurs = 1 _________ */
            DisplayStepOctaveGroupPtr getDisplayStepOctaveGroup() const;
            void setDisplayStepOctaveGroup( const DisplayStepOctaveGroupPtr& value );
            bool getHasDisplayStepOctaveGroup() const;
            void setHasDisplayStepOctaveGroup( const bool value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            DisplayStepOctaveGroupPtr myDisplayStepOctaveGroup;
            bool myHasDisplayStepOctaveGroup;
        };
    }
}
