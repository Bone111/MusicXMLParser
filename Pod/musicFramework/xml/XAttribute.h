// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include <iostream>
#include <memory>

namespace mx
{
    namespace xml
    {

        class XAttribute;
        using XAttributePtr = std::shared_ptr<XAttribute>;
        
        class XAttribute;
        using XAttributePtr = std::shared_ptr<XAttribute>;
        
        class XAttributeIterator;
        using XAttributeIteratorPtr = std::shared_ptr<XAttributeIterator>;
        
        class XAttributeIterator;
        using XAttributeIteratorPtr = std::shared_ptr<XAttributeIterator>;
        
        class XElement;
        using XElementPtr = std::shared_ptr<XElement>;
        
        class XAttribute
        {
        public:
            virtual ~XAttribute() {}
            
            virtual bool getIsNull() const = 0;
            virtual std::string getName() const = 0;
            virtual std::string getValue() const = 0;
            
            virtual void setName( const std::string& name ) = 0;
            virtual void setValue( const std::string& name ) = 0;
        };
        
    }
}
