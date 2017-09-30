// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/MeasureAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( MeasureAttributes )
        MX_FORWARD_DECLARE_ELEMENT( MusicDataGroup )
        MX_FORWARD_DECLARE_ELEMENT( PartwiseMeasure )

        inline PartwiseMeasurePtr makePartwiseMeasure() { return std::make_shared<PartwiseMeasure>(); }

        class PartwiseMeasure : public ElementInterface
        {
        public:
            PartwiseMeasure();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            MeasureAttributesPtr getAttributes() const;
            void setAttributes( const MeasureAttributesPtr& value );

            /* _________ MusicDataGroup minOccurs = 1, maxOccurs = 1 _________ */
            MusicDataGroupPtr getMusicDataGroup() const;
            void setMusicDataGroup( const MusicDataGroupPtr& value );
            
            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            MX_MUTEX
            mutable MeasureAttributesPtr myAttributes;
            MusicDataGroupPtr myMusicDataGroup;
        };
    }
}
