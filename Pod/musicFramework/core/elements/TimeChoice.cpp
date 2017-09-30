// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/TimeChoice.h"
#include "../../core/FromXElement.h"
#include "../../core/elements/SenzaMisura.h"
#include "../../core/elements/TimeSignatureGroup.h"
#include "../../core/elements/BeatType.h"
#include "../../core/elements/Beats.h"
#include "../../core/elements/Interchangeable.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        TimeChoice::TimeChoice()
        :myChoice( Choice::timeSignature )
        ,myTimeSignatureGroupSet()
        ,mySenzaMisura( makeSenzaMisura() )
        {
            myTimeSignatureGroupSet.push_back( makeTimeSignatureGroup() );
        }


        bool TimeChoice::hasAttributes() const
        {
            return false;
        }


        std::ostream& TimeChoice::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& TimeChoice::streamName( std::ostream& os ) const
        {
            return os;
        }


        bool TimeChoice::hasContents() const
        {
            return true;
        }


        std::ostream& TimeChoice::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            switch ( myChoice )
            {
                case Choice::timeSignature:
                {
                    for( auto x : myTimeSignatureGroupSet )
                    {
                        x->streamContents( os, indentLevel, isOneLineOnly );
                    }
                }
                    break;
                case Choice::senzaMisura:
                {
                    mySenzaMisura->toStream( os, indentLevel );
                }
                    break;
                default:
                    break;
            }
            return os;
        }


        TimeChoice::Choice TimeChoice::getChoice() const
        {
            return myChoice;
        }


        void TimeChoice::setChoice( const Choice value )
        {
            myChoice = value;
        }


        const TimeSignatureGroupSet& TimeChoice::getTimeSignatureGroupSet() const
        {
            return myTimeSignatureGroupSet;
        }
        
        
        void TimeChoice::removeTimeSignatureGroup( const TimeSignatureGroupSetIterConst& value )
        {
            if ( value != myTimeSignatureGroupSet.cend() )
            {
                myTimeSignatureGroupSet.erase( value );
            }
        }
        
        
        void TimeChoice::addTimeSignatureGroup( const TimeSignatureGroupPtr& value )
        {
            if ( value )
            {
                myTimeSignatureGroupSet.push_back( value );
            }
        }
        
        
        void TimeChoice::clearTimeSignatureGroupSet()
        {
            myTimeSignatureGroupSet.clear();
            myTimeSignatureGroupSet.push_back( makeTimeSignatureGroup() );
        }
        
        
        TimeSignatureGroupPtr TimeChoice::getTimeSignatureGroup( const TimeSignatureGroupSetIterConst& setIterator ) const
        {
            if( setIterator != myTimeSignatureGroupSet.cend() )
            {
                return *setIterator;
            }
            return TimeSignatureGroupPtr();
        }


        SenzaMisuraPtr TimeChoice::getSenzaMisura() const
        {
            return mySenzaMisura;
        }


        void TimeChoice::setSenzaMisura( const SenzaMisuraPtr& value )
        {
            if ( value )
            {
                mySenzaMisura = value;
            }
        }


        MX_FROM_XELEMENT_UNUSED( TimeChoice );

    }
}
