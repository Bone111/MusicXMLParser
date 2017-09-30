// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/GroupingAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( GroupingAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Feature )
        MX_FORWARD_DECLARE_ELEMENT( Grouping )

        inline GroupingPtr makeGrouping() { return std::make_shared<Grouping>(); }

        class Grouping : public ElementInterface
        {
        public:
            Grouping();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            GroupingAttributesPtr getAttributes() const;
            void setAttributes( const GroupingAttributesPtr& value );

            /* _________ Feature minOccurs = 0, maxOccurs = unbounded _________ */
            const FeatureSet& getFeatureSet() const;
            void addFeature( const FeaturePtr& value );
            void removeFeature( const FeatureSetIterConst& value );
            void clearFeatureSet();
            FeaturePtr getFeature( const FeatureSetIterConst& setIterator ) const;

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            GroupingAttributesPtr myAttributes;
            FeatureSet myFeatureSet;
        };
    }
}
