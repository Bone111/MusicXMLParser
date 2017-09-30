// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/DisplayStepOctaveGroup.h"
#include "../../core/FromXElement.h"
#include "../../core/elements/DisplayOctave.h"
#include "../../core/elements/DisplayStep.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        DisplayStepOctaveGroup::DisplayStepOctaveGroup()
        :myDisplayStep( makeDisplayStep() )
        ,myDisplayOctave( makeDisplayOctave() )
        {}


        bool DisplayStepOctaveGroup::hasAttributes() const
        {
            return false;
        }


        std::ostream& DisplayStepOctaveGroup::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& DisplayStepOctaveGroup::streamName( std::ostream& os ) const
        {
            return os;
        }


        bool DisplayStepOctaveGroup::hasContents() const
        {
            return true;
        }


        std::ostream& DisplayStepOctaveGroup::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( isOneLineOnly );
            myDisplayStep->toStream( os, indentLevel );
            os << std::endl;
            myDisplayOctave->toStream( os, indentLevel );
            return os;
        }


        DisplayStepPtr DisplayStepOctaveGroup::getDisplayStep() const
        {
            return myDisplayStep;
        }


        void DisplayStepOctaveGroup::setDisplayStep( const DisplayStepPtr& value )
        {
            if ( value )
            {
                myDisplayStep = value;
            }
        }


        DisplayOctavePtr DisplayStepOctaveGroup::getDisplayOctave() const
        {
            return myDisplayOctave;
        }


        void DisplayStepOctaveGroup::setDisplayOctave( const DisplayOctavePtr& value )
        {
            if ( value )
            {
                myDisplayOctave = value;
            }
        }
        
        
        bool DisplayStepOctaveGroup::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            bool isSuccess = true;
            bool isDisplayStepFound = false;
            bool isDisplayOctaveFound = false;
            
            for( auto it = xelement.begin(); it != xelement.end(); ++it )
            {
                const std::string elementName = it->getName();
                
                if( elementName == "display-step" )
                {
                    isDisplayStepFound = true;
                    isSuccess &= myDisplayStep->fromXElement( message, *it );
                }
                else if( elementName == "display-octave" )
                {
                    isDisplayOctaveFound = true;
                    isSuccess &= myDisplayOctave->fromXElement( message, *it );
                }
                else
                {
                    if( !isDisplayStepFound )
                    {
                        isSuccess = false;
                        message << "DisplayStepOctaveGroup: 'display-step' element is required but was not found" << std::endl;
                    }
                    if( !isDisplayOctaveFound )
                    {
                        isSuccess = false;
                        message << "DisplayStepOctaveGroup: 'display-octave' element is required but was not found" << std::endl;
                    }
                    break;
                }
            }
            MX_RETURN_IS_SUCCESS;
        }

    }
}
