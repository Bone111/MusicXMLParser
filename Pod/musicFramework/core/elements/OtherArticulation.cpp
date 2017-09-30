// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/OtherArticulation.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        OtherArticulation::OtherArticulation()
        :myValue()
        ,myAttributes( std::make_shared<OtherArticulationAttributes>() )
        {}


        OtherArticulation::OtherArticulation( const XsString& value )
        :myValue( value )
        ,myAttributes( std::make_shared<OtherArticulationAttributes>() )
        {}


        bool OtherArticulation::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool OtherArticulation::hasContents() const
        {
            return true;
        }


        std::ostream& OtherArticulation::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& OtherArticulation::streamName( std::ostream& os ) const
        {
            os << "other-articulation";
            return os;
        }


        std::ostream& OtherArticulation::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly  ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            os << myValue;
            return os;
        }


        OtherArticulationAttributesPtr OtherArticulation::getAttributes() const
        {
            return myAttributes;
        }


        void OtherArticulation::setAttributes( const OtherArticulationAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        XsString OtherArticulation::getValue() const
        {
            return myValue;
        }


        void OtherArticulation::setValue( const XsString& value )
        {
            myValue = value;
        }


        bool OtherArticulation::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            bool isSuccess = true;
            isSuccess &= myAttributes->fromXElement( message, xelement );
            myValue.setValue( xelement.getValue() );
            MX_RETURN_IS_SUCCESS;
        }

    }
}
