// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/FullNoteGroup.h"
#include "../../core/FromXElement.h"
#include "../../core/elements/Chord.h"
#include "../../core/elements/FullNoteTypeChoice.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        FullNoteGroup::FullNoteGroup()
        :myChord( makeChord() )
        ,myHasChord( false )
        ,myFullNoteTypeChoice( nullptr )
        {}


        bool FullNoteGroup::hasAttributes() const
        {
            return false;
        }


        std::ostream& FullNoteGroup::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& FullNoteGroup::streamName( std::ostream& os ) const
        {
            return os;
        }


        bool FullNoteGroup::hasContents() const
        {
            return true;
        }


        std::ostream& FullNoteGroup::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            if ( myHasChord )
            {
                myChord->toStream( os, indentLevel );
                os << std::endl;
            }
            getFullNoteTypeChoice()->streamContents( os, indentLevel, isOneLineOnly );
            isOneLineOnly = false;
            return os;
        }


        ChordPtr FullNoteGroup::getChord() const
        {
            return myChord;
        }


        void FullNoteGroup::setChord( const ChordPtr& value )
        {
            if ( value )
            {
                myChord = value;
            }
        }


        bool FullNoteGroup::getHasChord() const
        {
            return myHasChord;
        }


        void FullNoteGroup::setHasChord( const bool value )
        {
            myHasChord = value;
        }


        FullNoteTypeChoicePtr FullNoteGroup::getFullNoteTypeChoice() const
        {
            MX_LOCK
            MX_JIT_ALLOCATE( FullNoteTypeChoice );
            return myFullNoteTypeChoice;
        }


        void FullNoteGroup::setFullNoteTypeChoice( const FullNoteTypeChoicePtr& value )
        {
            if ( value )
            {
                myFullNoteTypeChoice = value;
            }
        }
        
        
        MX_FROM_XELEMENT_UNUSED( FullNoteGroup );

    }
}
