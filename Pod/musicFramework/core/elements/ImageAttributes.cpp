// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/ImageAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        ImageAttributes::ImageAttributes()
        :source()
        ,type()
        ,defaultX()
        ,defaultY()
        ,relativeX()
        ,relativeY()
        ,halign( LeftCenterRight::center )
        ,hasSource( true )
        ,hasType( true )
        ,hasDefaultX( false )
        ,hasDefaultY( false )
        ,hasRelativeX( false )
        ,hasRelativeY( false )
        ,hasHalign( false )
        {}


        bool ImageAttributes::hasValues() const
        {
            return hasSource ||
            hasType ||
            hasDefaultX ||
            hasDefaultY ||
            hasRelativeX ||
            hasRelativeY ||
            hasHalign;
        }


        std::ostream& ImageAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, source, "source", hasSource );
                streamAttribute( os, type, "type", hasType );
                streamAttribute( os, defaultX, "default-x", hasDefaultX );
                streamAttribute( os, defaultY, "default-y", hasDefaultY );
                streamAttribute( os, relativeX, "relative-x", hasRelativeX );
                streamAttribute( os, relativeY, "relative-y", hasRelativeY );
                streamAttribute( os, halign, "halign", hasHalign );
            }
            return os;
        }


        bool ImageAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "ImageAttributes";
            bool isSuccess = true;
            bool isSourceFound = false;
            bool isTypeFound = false;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, source, isSourceFound, "source" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, type, isTypeFound, "type" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, defaultX, hasDefaultX, "default-x" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, defaultY, hasDefaultY, "default-y" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, relativeX, hasRelativeX, "relative-x" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, relativeY, hasRelativeY, "relative-y" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, halign, hasHalign, "halign", &parseLeftCenterRight ) ) { continue; }
            }
        
            if( !isSourceFound )
            {
                isSuccess = false;
                message << className << ": 'number' is a required attribute but was not found" << std::endl;
            }
            if( !isTypeFound )
            {
                isSuccess = false;
                message << className << ": 'number' is a required attribute but was not found" << std::endl;
            }
        
            return isSuccess;
        }

    }
}
