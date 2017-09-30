// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/ClefAttributes.h"
#include "../../core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        ClefAttributes::ClefAttributes()
        :number()
        ,additional( YesNo::no )
        ,size()
        ,afterBarline( YesNo::no )
        ,defaultX()
        ,defaultY()
        ,relativeX()
        ,relativeY()
        ,fontFamily()
        ,fontStyle( FontStyle::normal )
        ,fontSize( CssFontSize::medium )
        ,fontWeight( FontWeight::normal )
        ,color()
        ,printObject( YesNo::no )
        ,hasNumber( false )
        ,hasAdditional( false )
        ,hasSize( false )
        ,hasAfterBarline( false )
        ,hasDefaultX( false )
        ,hasDefaultY( false )
        ,hasRelativeX( false )
        ,hasRelativeY( false )
        ,hasFontFamily( false )
        ,hasFontStyle( false )
        ,hasFontSize( false )
        ,hasFontWeight( false )
        ,hasColor( false )
        ,hasPrintObject( false )
        {}


        bool ClefAttributes::hasValues() const
        {
            return hasNumber ||
            hasAdditional ||
            hasSize ||
            hasAfterBarline ||
            hasDefaultX ||
            hasDefaultY ||
            hasRelativeX ||
            hasRelativeY ||
            hasFontFamily ||
            hasFontStyle ||
            hasFontSize ||
            hasFontWeight ||
            hasColor ||
            hasPrintObject;
        }


        std::ostream& ClefAttributes::toStream( std::ostream& os ) const
        {
            if ( hasValues() )
            {
                streamAttribute( os, number, "number", hasNumber );
                streamAttribute( os, additional, "additional", hasAdditional );
                streamAttribute( os, size, "size", hasSize );
                streamAttribute( os, afterBarline, "after-barline", hasAfterBarline );
                streamAttribute( os, defaultX, "default-x", hasDefaultX );
                streamAttribute( os, defaultY, "default-y", hasDefaultY );
                streamAttribute( os, relativeX, "relative-x", hasRelativeX );
                streamAttribute( os, relativeY, "relative-y", hasRelativeY );
                streamAttribute( os, fontFamily, "font-family", hasFontFamily );
                streamAttribute( os, fontStyle, "font-style", hasFontStyle );
                streamAttribute( os, fontSize, "font-size", hasFontSize );
                streamAttribute( os, fontWeight, "font-weight", hasFontWeight );
                streamAttribute( os, color, "color", hasColor );
                streamAttribute( os, printObject, "print-object", hasPrintObject );
            }
            return os;
        }


        bool ClefAttributes::fromXElement( std::ostream& message, xml::XElement& xelement )
        {
            const char* const className = "ClefAttributes";
            bool isSuccess = true;
        
            auto it = xelement.attributesBegin();
            auto endIter = xelement.attributesEnd();
        
            for( ; it != endIter; ++it )
            {
                if( parseAttribute( message, it, className, isSuccess, number, hasNumber, "number" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, additional, hasAdditional, "additional", &parseYesNo ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, size, hasSize, "size", &parseSymbolSize ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, afterBarline, hasAfterBarline, "after-barline", &parseYesNo ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, defaultX, hasDefaultX, "default-x" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, defaultY, hasDefaultY, "default-y" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, relativeX, hasRelativeX, "relative-x" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, relativeY, hasRelativeY, "relative-y" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, fontFamily, hasFontFamily, "font-family" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, fontStyle, hasFontStyle, "font-style", &parseFontStyle ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, fontSize, hasFontSize, "font-size" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, fontWeight, hasFontWeight, "font-weight", &parseFontWeight ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, color, hasColor, "color" ) ) { continue; }
                if( parseAttribute( message, it, className, isSuccess, printObject, hasPrintObject, "print-object", &parseYesNo ) ) { continue; }
            }
        
        
            MX_RETURN_IS_SUCCESS;
        }

    }
}
