// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/MetronomeAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( MetronomeAttributes )
        MX_FORWARD_DECLARE_ELEMENT( BeatUnitPerOrNoteRelationNoteChoice )
        MX_FORWARD_DECLARE_ELEMENT( Metronome )

        inline MetronomePtr makeMetronome() { return std::make_shared<Metronome>(); }

        class Metronome : public ElementInterface
        {
        public:
            Metronome();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            MetronomeAttributesPtr getAttributes() const;
            void setAttributes( const MetronomeAttributesPtr& value );
            BeatUnitPerOrNoteRelationNoteChoicePtr getBeatUnitPerOrNoteRelationNoteChoice() const;
            void setBeatUnitPerOrNoteRelationNoteChoice( const BeatUnitPerOrNoteRelationNoteChoicePtr& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            MetronomeAttributesPtr myAttributes;
            BeatUnitPerOrNoteRelationNoteChoicePtr myBeatUnitPerOrNoteRelationNoteChoice;
        };
    }
}
