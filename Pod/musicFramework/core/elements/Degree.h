// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../../core/ForwardDeclare.h"
#include "../../core/ElementInterface.h"
#include "../../core/elements/DegreeAttributes.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace mx
{
    namespace core
    {

        MX_FORWARD_DECLARE_ATTRIBUTES( DegreeAttributes )
        MX_FORWARD_DECLARE_ELEMENT( DegreeAlter )
        MX_FORWARD_DECLARE_ELEMENT( DegreeType )
        MX_FORWARD_DECLARE_ELEMENT( DegreeValue )
        MX_FORWARD_DECLARE_ELEMENT( Degree )

        inline DegreePtr makeDegree() { return std::make_shared<Degree>(); }

        class Degree : public ElementInterface
        {
        public:
            Degree();

            virtual bool hasAttributes() const;
            virtual std::ostream& streamAttributes( std::ostream& os ) const;
            virtual std::ostream& streamName( std::ostream& os ) const;
            virtual bool hasContents() const;
            virtual std::ostream& streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const;
            DegreeAttributesPtr getAttributes() const;
            void setAttributes( const DegreeAttributesPtr& value );

            /* _________ DegreeValue minOccurs = 1, maxOccurs = 1 _________ */
            DegreeValuePtr getDegreeValue() const;
            void setDegreeValue( const DegreeValuePtr& value );

            /* _________ DegreeAlter minOccurs = 1, maxOccurs = 1 _________ */
            DegreeAlterPtr getDegreeAlter() const;
            void setDegreeAlter( const DegreeAlterPtr& value );

            /* _________ DegreeType minOccurs = 1, maxOccurs = 1 _________ */
            DegreeTypePtr getDegreeType() const;
            void setDegreeType( const DegreeTypePtr& value );

            bool fromXElement( std::ostream& message, xml::XElement& xelement );

        private:
            DegreeAttributesPtr myAttributes;
            DegreeValuePtr myDegreeValue;
            DegreeAlterPtr myDegreeAlter;
            DegreeTypePtr myDegreeType;
        };
    }
}
