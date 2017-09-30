// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../../core/elements/EditorialGroup.h"
#include "../../core/FromXElement.h"
#include "../../core/elements/Footnote.h"
#include "../../core/elements/Level.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        EditorialGroup::EditorialGroup()
        :myFootnote( makeFootnote() )
        ,myHasFootnote( false )
        ,myLevel( makeLevel() )
        ,myHasLevel( false )
        {}


        bool EditorialGroup::hasAttributes() const
        {
            return false;
        }


        std::ostream& EditorialGroup::streamAttributes( std::ostream& os ) const
        {
            return os;
        }


        std::ostream& EditorialGroup::streamName( std::ostream& os ) const
        {
            return os;
        }


        bool EditorialGroup::hasContents() const
        {
            return myHasFootnote || myHasLevel;
        }


        std::ostream& EditorialGroup::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            isOneLineOnly = true;
            if ( myHasFootnote )
            {
                myFootnote->toStream( os, indentLevel );
                if ( myHasLevel )
                {
                    os << std::endl;
                    isOneLineOnly = false;
                }
            }
            if ( myHasLevel )
            {
                myLevel->toStream( os, indentLevel );
            }
            return os;
        }


        FootnotePtr EditorialGroup::getFootnote() const
        {
            return myFootnote;
        }


        void EditorialGroup::setFootnote( const FootnotePtr& value )
        {
            if ( value )
            {
                myFootnote = value;
            }
        }


        bool EditorialGroup::getHasFootnote() const
        {
            return myHasFootnote;
        }


        void EditorialGroup::setHasFootnote( const bool value )
        {
            myHasFootnote = value;
        }


        LevelPtr EditorialGroup::getLevel() const
        {
            return myLevel;
        }


        void EditorialGroup::setLevel( const LevelPtr& value )
        {
            if ( value )
            {
                myLevel = value;
            }
        }


        bool EditorialGroup::getHasLevel() const
        {
            return myHasLevel;
        }


        void EditorialGroup::setHasLevel( const bool value )
        {
            myHasLevel = value;
        }

        
        MX_FROM_XELEMENT_UNUSED( EditorialGroup );
    }
}
