// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/KeyAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    
    namespace xml
    {
        class XElementIterator;
    }
    
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( KeyAttributes )
        MX_FORWARD_DECLARE_ELEMENT( KeyChoice )
        MX_FORWARD_DECLARE_ELEMENT( KeyOctave )
        MX_FORWARD_DECLARE_ELEMENT( Key )

        inline KeyPtr makeKey() { return std::make_shared<Key>(); }

        class Key : public ElementInterface
        {
        public:
            Key();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            KeyAttributesPtr getAttributes() const;
            void setAttributes( const KeyAttributesPtr& value );
            KeyChoicePtr getKeyChoice() const;
            void setKeyChoice( const KeyChoicePtr& value );
            const KeyOctaveSet& getKeyOctaveSet() const;
            void removeKeyOctave( const KeyOctaveSetIterConst& value );
            void addKeyOctave( const KeyOctavePtr& value );
            void clearKeyOctaveSet();

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            KeyAttributesPtr myAttributes;
            KeyChoicePtr myKeyChoice;
            KeyOctaveSet myKeyOctaveSet;
            
            bool importTraditionalKey( std::ostream& message, xml::XElementIterator& iter, xml::XElementIterator& endIter, bool& isSuccess );
            bool importNonTraditionalKey( std::ostream& message, xml::XElementIterator& iter, xml::XElementIterator& endIter, bool& isSuccess );
        };
    }
}
