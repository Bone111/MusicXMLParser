// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/RootStepAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        RootStepAttributes::RootStepAttributes()
        :text()
        ,defaultX()
        ,defaultY()
        ,relativeX()
        ,relativeY()
        ,fontFamily()
        ,fontStyle( FontStyle::normal )
        ,fontSize( FontSize{ CssFontSize::medium } )
        ,fontWeight( FontWeight::normal )
        ,hasText( false )
        ,hasDefaultX( false )
        ,hasDefaultY( false )
        ,hasRelativeX( false )
        ,hasRelativeY( false )
        ,hasFontFamily( false )
        ,hasFontStyle( false )
        ,hasFontSize( false )
        ,hasFontWeight( false )
        {}


        bool RootStepAttributes::hasValues() const
        {
            return hasText ||
            hasDefaultX ||
            hasDefaultY ||
            hasRelativeX ||
            hasRelativeY ||
            hasFontFamily ||
            hasFontStyle ||
            hasFontSize ||
            hasFontWeight;
        }


        std::ostream& RootStepAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, text, "text", hasText );
                streamAttribute( os, defaultX, "default-x", hasDefaultX );
                streamAttribute( os, defaultY, "default-y", hasDefaultY );
                streamAttribute( os, relativeX, "relative-x", hasRelativeX );
                streamAttribute( os, relativeY, "relative-y", hasRelativeY );
                streamAttribute( os, fontFamily, "font-family", hasFontFamily );
                streamAttribute( os, fontStyle, "font-style", hasFontStyle );
                streamAttribute( os, fontSize, "font-size", hasFontSize );
                streamAttribute( os, fontWeight, "font-weight", hasFontWeight );
            }
            return os;
        }


        bool RootStepAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "RootStepAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, text, hasText, "text" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, defaultX, hasDefaultX, "default-x" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, defaultY, hasDefaultY, "default-y" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, relativeX, hasRelativeX, "relative-x" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, relativeY, hasRelativeY, "relative-y" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, fontFamily, hasFontFamily, "font-family" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, fontStyle, hasFontStyle, "font-style", &parseFontStyle ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, fontSize, hasFontSize, "font-size" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, fontWeight, hasFontWeight, "font-weight", &parseFontWeight ) ) { continue; }
            }
        
        
            return isSuccess;
        }

    }
}
