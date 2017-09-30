// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/TimewisePart.h"
#include "../../core/FromXElement.h"
#include "../../core/elements/MusicDataGroup.h"
#include "../../core/elements/MusicDataChoice.h"
#include "../../core/elements/Backup.h"
#include "../../core/elements/Barline.h"
#include "../../core/elements/Bookmark.h"
#include "../../core/elements/Direction.h"
#include "../../core/elements/FiguredBass.h"
#include "../../core/elements/Forward.h"
#include "../../core/elements/Grouping.h"
#include "../../core/elements/Harmony.h"
#include "../../core/elements/Link.h"
#include "../../core/elements/Note.h"
#include "../../core/elements/Print.h"
#include "../../core/elements/Properties.h"
#include "../../core/elements/Sound.h"

#include <iostream>

namespace mx
{
    namespace core
    {
        TimewisePart::TimewisePart()
        :myAttributes( std::make_shared<PartAttributes>() )
        ,myMusicDataGroup( makeMusicDataGroup() )
        {}


        bool TimewisePart::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        std::ostream& TimewisePart::streamAttributes( std::ostream& os ) const
        {
            return myAttributes->toStream( os );
        }


        std::ostream& TimewisePart::streamName( std::ostream& os ) const
        {
            os << "part";
            return os;
        }


        bool TimewisePart::hasContents() const
        {
            return myMusicDataGroup->hasContents();
        }


        std::ostream& TimewisePart::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            if ( hasContents() )
            {
                os << std::endl;
                myMusicDataGroup->streamContents( os, indentLevel+1, isOneLineOnly );
                os << std::endl;
                isOneLineOnly = false;
            }
            else
            {
                isOneLineOnly = true;
            }
            return os;
        }


        PartAttributesPtr TimewisePart::getAttributes() const
        {
            return myAttributes;
        }


        void TimewisePart::setAttributes( const PartAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        MusicDataGroupPtr TimewisePart::getMusicDataGroup() const
        {
            return myMusicDataGroup;
        }


        void TimewisePart::setMusicDataGroup( const MusicDataGroupPtr& value )
        {
            if ( value )
            {
                myMusicDataGroup = value;
            }
        }
        
        
        bool TimewisePart::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            bool isSuccess = true;
            bool isFirstMusicDataChoiceAdded = false;
            isSuccess &= myAttributes->fromXElement( message, xelement );
            
            for( auto it = xelement.begin(); it != xelement.end(); ++it )
            {
                const std::string elementName = it->getName();
                
                auto choiceObject = makeMusicDataChoice();
                bool choiceObjectShouldBeAdded = true;
                
                if( elementName == "note" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::note );
                    isSuccess &= choiceObject->getNote()->fromXElement( message, *it );
                }
                else if ( elementName == "backup" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::backup );
                    isSuccess &= choiceObject->getBackup()->fromXElement( message, *it );
                }
                else if ( elementName == "forward" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::forward );
                    isSuccess &= choiceObject->getForward()->fromXElement( message, *it );
                }
                else if ( elementName == "direction" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::direction );
                    isSuccess &= choiceObject->getDirection()->fromXElement( message, *it );
                }
                else if ( elementName == "attributes" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::properties );
                    isSuccess &= choiceObject->getProperties()->fromXElement( message, *it );
                }
                else if ( elementName == "harmony" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::harmony );
                    isSuccess &= choiceObject->getHarmony()->fromXElement( message, *it );
                }
                else if ( elementName == "figured-bass" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::figuredBass );
                    isSuccess &= choiceObject->getFiguredBass()->fromXElement( message, *it );
                }
                else if ( elementName == "print" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::print );
                    isSuccess &= choiceObject->getPrint()->fromXElement( message, *it );
                }
                else if ( elementName == "sound" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::sound );
                    isSuccess &= choiceObject->getSound()->fromXElement( message, *it );
                }
                else if ( elementName == "barline" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::barline );
                    isSuccess &= choiceObject->getBarline()->fromXElement( message, *it );
                }
                else if ( elementName == "grouping" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::grouping );
                    isSuccess &= choiceObject->getGrouping()->fromXElement( message, *it );
                }
                else if ( elementName == "link" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::link );
                    isSuccess &= choiceObject->getLink()->fromXElement( message, *it );
                }
                else if ( elementName == "bookmark" )
                {
                    choiceObject->setChoice( MusicDataChoice::Choice::bookmark );
                    isSuccess &= choiceObject->getBookmark()->fromXElement( message, *it );
                }
                else
                {
                    choiceObjectShouldBeAdded = false;
                }
                
                if( choiceObjectShouldBeAdded )
                {
                    if( !isFirstMusicDataChoiceAdded && myMusicDataGroup->getMusicDataChoiceSet().size() == 1 )
                    {
                        myMusicDataGroup->addMusicDataChoice( choiceObject );
                        myMusicDataGroup->removeMusicDataChoice( myMusicDataGroup->getMusicDataChoiceSet().cbegin() );
                        isFirstMusicDataChoiceAdded = true;
                    }
                    else
                    {
                        myMusicDataGroup->addMusicDataChoice( choiceObject );
                        isFirstMusicDataChoiceAdded = true;
                    }
                }
            }
            
            MX_RETURN_IS_SUCCESS;
        }

    }
}
