// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/Strings.h"
#include "../../core/elements/FeatureAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( FeatureAttributes )
        MX_FORWARD_DECLARE_ELEMENT( Feature )

        inline FeaturePtr makeFeature() { return std::make_shared<Feature>(); }
		inline FeaturePtr makeFeature( const XsString& value ) { return std::make_shared<Feature>( value ); }
		inline FeaturePtr makeFeature( XsString&& value ) { return std::make_shared<Feature>( std::move( value ) ); }

        class Feature : public ElementInterface
        {
        public:
            Feature();
            Feature( const XsString& value );

            virtual bool hasAttributes() const;
            virtual bool hasContents() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            FeatureAttributesPtr getAttributes() const;
            void setAttributes( const FeatureAttributesPtr& attributes );
            XsString getValue() const;
            void setValue( const XsString& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            XsString myValue;
            FeatureAttributesPtr myAttributes;
        };
    }
}
