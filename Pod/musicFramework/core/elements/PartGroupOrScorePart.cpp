// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/PartGroupOrScorePart.h"
#include "../../core/FromXElement.h"
#include "../../core/elements/PartGroup.h"
#include "../../core/elements/ScorePart.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        PartGroupOrScorePart::PartGroupOrScorePart()
        :myChoice( Choice::partGroup )
        ,myPartGroup( makePartGroup() )
        ,myScorePart( makeScorePart() )
        {}


        bool PartGroupOrScorePart::hasAttributes() const
        {
            return false;
        }


        std::ostream& PartGroupOrScorePart::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& PartGroupOrScorePart::streamName( std::ostream& os ) const
        {
            return os;
        }


        bool PartGroupOrScorePart::hasContents() const
        {
            return ( myChoice == Choice::partGroup && myPartGroup->hasContents() )
            || ( myChoice == Choice::scorePart && myScorePart->hasContents() );
        }


        std::ostream& PartGroupOrScorePart::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            switch ( myChoice )
            {
                case Choice::partGroup:
                    myPartGroup->toStream( os, indentLevel );
                    break;
                case Choice::scorePart:
                    myScorePart->toStream( os, indentLevel );
                    break;
                default:
                    break;
            }
            isOneLineOnly = false;
            return os;
        }


        PartGroupOrScorePart::Choice PartGroupOrScorePart::getChoice() const
        {
            return myChoice;
        }


        void PartGroupOrScorePart::setChoice( const PartGroupOrScorePart::Choice value )
        {
            myChoice = value;
        }


        PartGroupPtr PartGroupOrScorePart::getPartGroup() const
        {
            return myPartGroup;
        }


        void PartGroupOrScorePart::setPartGroup( const PartGroupPtr& value )
        {
            if ( value )
            {
                myPartGroup = value;
            }
        }


        ScorePartPtr PartGroupOrScorePart::getScorePart() const
        {
            return myScorePart;
        }


        void PartGroupOrScorePart::setScorePart( const ScorePartPtr& value )
        {
            if ( value )
            {
                myScorePart = value;
            }
        }
        
        
        MX_FROM_XELEMENT_UNUSED( PartGroupOrScorePart )

    }
}
