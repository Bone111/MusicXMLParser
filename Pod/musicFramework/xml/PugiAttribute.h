// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../xml/XAttribute.h"
#include "../pugixml/pugixml.hpp"

#include <memory>


namespace mx
{
    namespace xml
    {
        class PugiAttribute;
        using PugiAttributePtr = std::shared_ptr<PugiAttribute>;
        
        class XDoc;
        using XDocCPtr = std::shared_ptr<const XDoc>;
        using XDocCWPtr = std::weak_ptr<const XDoc>;

        class PugiAttribute : public XAttribute
        {
        public:
            PugiAttribute();

            PugiAttribute(
                const pugi::xml_attribute& attribute,
                const pugi::xml_node& parentElement,
                const XDocCPtr& parentXDoc );
            
            PugiAttribute( const PugiAttribute& other ) = default;
            PugiAttribute( PugiAttribute&& other ) = default;
            PugiAttribute& operator=( const PugiAttribute& other ) = default;
            PugiAttribute& operator=( PugiAttribute&& other ) = default;

            virtual bool getIsNull() const override;
            virtual std::string getName() const override;
            virtual std::string getValue() const override;
            
            virtual void setName( const std::string& name ) override;
            virtual void setValue( const std::string& name ) override;
            
        private:
            pugi::xml_attribute myAttribute;
            pugi::xml_node myParentElement;
            XDocCWPtr myXDoc;
        };
    }
}
