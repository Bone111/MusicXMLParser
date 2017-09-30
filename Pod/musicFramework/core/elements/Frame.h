// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/FrameAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( FrameAttributes )
        MX_FORWARD_DECLARE_ELEMENT( FirstFret )
        MX_FORWARD_DECLARE_ELEMENT( FrameFrets )
        MX_FORWARD_DECLARE_ELEMENT( FrameNote )
        MX_FORWARD_DECLARE_ELEMENT( FrameStrings )
        MX_FORWARD_DECLARE_ELEMENT( Frame )

        inline FramePtr makeFrame() { return std::make_shared<Frame>(); }

        class Frame : public ElementInterface
        {
        public:
            Frame();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            FrameAttributesPtr getAttributes() const;
            void setAttributes( const FrameAttributesPtr& value );

            /* _________ FrameStrings minOccurs = 1, maxOccurs = 1 _________ */
            FrameStringsPtr getFrameStrings() const;
            void setFrameStrings( const FrameStringsPtr& value );

            /* _________ FrameFrets minOccurs = 1, maxOccurs = 1 _________ */
            FrameFretsPtr getFrameFrets() const;
            void setFrameFrets( const FrameFretsPtr& value );

            /* _________ FirstFret minOccurs = 0, maxOccurs = 1 _________ */
            FirstFretPtr getFirstFret() const;
            void setFirstFret( const FirstFretPtr& value );
            bool getHasFirstFret() const;
            void setHasFirstFret( const bool value );

            /* _________ FrameNote minOccurs = 1, maxOccurs = unbounded _________ */
            const FrameNoteSet& getFrameNoteSet() const;
            void addFrameNote( const FrameNotePtr& value );
            void removeFrameNote( const FrameNoteSetIterConst& value );
            void clearFrameNoteSet();
            FrameNotePtr getFrameNote( const FrameNoteSetIterConst& setIterator ) const;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            FrameAttributesPtr myAttributes;
            FrameStringsPtr myFrameStrings;
            FrameFretsPtr myFrameFrets;
            FirstFretPtr myFirstFret;
            bool myHasFirstFret;
            FrameNoteSet myFrameNoteSet;
        };
    }
}
