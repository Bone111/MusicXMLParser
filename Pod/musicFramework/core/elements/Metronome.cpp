// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/Metronome.h"
#include "../../core/FromXElement.h"
#include "../../core/elements/BeatUnitPerOrNoteRelationNoteChoice.h"
#include "../../core/elements/BeatUnitGroup.h"
#include "../../core/elements/PerMinuteOrBeatUnitChoice.h"
#include "../../core/elements/BeatUnitGroup.h"
#include "../../core/elements/BeatUnitPer.h"
#include "../../core/elements/PerMinute.h"
#include "../../core/elements/NoteRelationNote.h"
#include "../../core/elements/MetronomeNote.h"
#include "../../core/elements/MetronomeRelationGroup.h"
#include "../../core/elements/MetronomeRelation.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Metronome::Metronome()
        :myAttributes( std::make_shared<MetronomeAttributes>() )
        ,myBeatUnitPerOrNoteRelationNoteChoice( makeBeatUnitPerOrNoteRelationNoteChoice() )
        {}


        bool Metronome::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        std::ostream& Metronome::streamAttributes( std::ostream& os ) const
        {
            myAttributes->toStream( os );
            return os;
        }


        std::ostream& Metronome::streamName( std::ostream& os ) const
        {
            return os << "metronome";
        }


        bool Metronome::hasContents() const
        {
            return true;
        }


        std::ostream& Metronome::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            os << std::endl;
            myBeatUnitPerOrNoteRelationNoteChoice->streamContents( os, indentLevel+1, isOneLineOnly );
            os << std::endl;
            isOneLineOnly = false;
            return os;
        }


        MetronomeAttributesPtr Metronome::getAttributes() const
        {
            return myAttributes;
        }


        void Metronome::setAttributes( const MetronomeAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        BeatUnitPerOrNoteRelationNoteChoicePtr Metronome::getBeatUnitPerOrNoteRelationNoteChoice() const
        {
            return myBeatUnitPerOrNoteRelationNoteChoice;
        }


        void Metronome::setBeatUnitPerOrNoteRelationNoteChoice( const BeatUnitPerOrNoteRelationNoteChoicePtr& value )
        {
            if ( value )
            {
                myBeatUnitPerOrNoteRelationNoteChoice = value;
            }
        }

        /*
         <xs:attributeGroup ref="justify"/>
         <xs:attributeGroup ref="print-style-align"/>
         <xs:attributeGroup ref="text-decoration"/>
         <xs:attributeGroup ref="text-rotation"/>
         <xs:attributeGroup ref="letter-spacing"/>
         <xs:attributeGroup ref="line-height"/>
         <xs:attribute ref="xml:lang"/>
         <xs:attribute ref="xml:space"/>
         <xs:attributeGroup ref="text-direction"/>
         <xs:attributeGroup ref="enclosure"/>*/

        bool Metronome::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            bool isSuccess = true;
            isSuccess &= myAttributes->fromXElement( message, xelement );
            
            auto iter = xelement.begin();
            auto endIter = xelement.end();
            
            for( ; iter != endIter; ++iter )
            {
                bool isIterIncremented = false;
                
                if( ( iter->getName() == "beat-unit" ) || ( iter->getName() == "beat-unit-dot" ) )
                {
                    myBeatUnitPerOrNoteRelationNoteChoice->setChoice( BeatUnitPerOrNoteRelationNoteChoice::Choice::beatUnitPer );
                    auto beatUnitGroup = myBeatUnitPerOrNoteRelationNoteChoice->getBeatUnitPer()->getBeatUnitGroup();
                    importGroup( message, iter, endIter, isSuccess, beatUnitGroup );
                    isIterIncremented = true;
                    ++iter;
                    
                    if( iter == endIter )
                    {
                        return false;
                    }
                    
                    if( ( iter->getName() == "beat-unit" ) || ( iter->getName() == "beat-unit-dot" ) )
                    {
                        auto beatUnitGroup2 = myBeatUnitPerOrNoteRelationNoteChoice->getBeatUnitPer()->getPerMinuteOrBeatUnitChoice()->getBeatUnitGroup();
                        myBeatUnitPerOrNoteRelationNoteChoice->getBeatUnitPer()->getPerMinuteOrBeatUnitChoice()->setChoice( PerMinuteOrBeatUnitChoice::Choice::beatUnitGroup );
                        importGroup( message, iter, endIter, isSuccess, beatUnitGroup2 );
                        isIterIncremented = true;
                        ++iter;
                    }
                    else if ( iter->getName() == "per-minute" )
                    {
                        myBeatUnitPerOrNoteRelationNoteChoice->getBeatUnitPer()->getPerMinuteOrBeatUnitChoice()->setChoice( PerMinuteOrBeatUnitChoice::Choice::perMinute );
                        myBeatUnitPerOrNoteRelationNoteChoice->getBeatUnitPer()->getPerMinuteOrBeatUnitChoice()->getPerMinute()->fromXElement( message, *iter );
                        isIterIncremented = true;
                        ++iter;
                    }
                }
                else if( ( iter->getName() == "metronome-note" ) )
                {
                    myBeatUnitPerOrNoteRelationNoteChoice->setChoice( BeatUnitPerOrNoteRelationNoteChoice::Choice::noteRelationNote );
                    auto noteRelationNote = myBeatUnitPerOrNoteRelationNoteChoice->getNoteRelationNote();
                    bool isFirstMetronomeNoteAdded = false;
                    
                    while( iter != endIter && iter->getName() == "metronome-note" )
                    {
                        auto metronomeNote = makeMetronomeNote();
                        isSuccess &= metronomeNote->fromXElement( message, *iter );
                        
                        if( !isFirstMetronomeNoteAdded && noteRelationNote->getMetronomeNoteSet().size() == 1 )
                        {
                            noteRelationNote->addMetronomeNote( metronomeNote );
                            noteRelationNote->removeMetronomeNote( noteRelationNote->getMetronomeNoteSet().cbegin() );
                            isFirstMetronomeNoteAdded = true;
                        }
                        else
                        {
                            noteRelationNote->addMetronomeNote( metronomeNote );
                            isFirstMetronomeNoteAdded = true;
                        }
                        isIterIncremented = true;
                        ++iter;
                    }
                    
                    if( iter == endIter )
                    {
                        MX_RETURN_IS_SUCCESS;
                    }
                    
                    if( iter->getName() == "metronome-relation" )
                    {
                        myBeatUnitPerOrNoteRelationNoteChoice->getNoteRelationNote()->setHasMetronomeRelationGroup( true );
                        auto metronomeRelationGroup = myBeatUnitPerOrNoteRelationNoteChoice->getNoteRelationNote()->getMetronomeRelationGroup();
                        isSuccess &= metronomeRelationGroup->getMetronomeRelation()->fromXElement( message, *iter );
                        ++iter;
                        isIterIncremented = true;
                        
                        if( iter == endIter )
                        {
                            MX_RETURN_IS_SUCCESS;
                        }
                        
                        if( iter->getName() == "metronome-note" )
                        {
                            myBeatUnitPerOrNoteRelationNoteChoice->getNoteRelationNote()->setHasMetronomeRelationGroup( true );
                            isSuccess &= metronomeRelationGroup->getMetronomeNote()->fromXElement( message, *iter );
                            ++iter;
                            isIterIncremented = true;
                            if( iter == endIter )
                            {
                                MX_RETURN_IS_SUCCESS;
                            }
                        }
                    }
                    
                }
                
                if( isIterIncremented )
                {
                    --iter;
                }
            }
            
            MX_RETURN_IS_SUCCESS;
        }

    }
}
