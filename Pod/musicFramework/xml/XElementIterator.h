// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "../xml/XElement.h"
#include "../xml/XElementIterImpl.h"

#include <iostream>
#include <memory>

namespace mx
{
    namespace xml
    {
        class XElementIterator final
        {

        public:
            XElementIterator();
            XElementIterator( const XElementIterImpl& impl );
            XElementIterator( const XElementIterator& other );
            XElementIterator( XElementIterator&& other ) = default;
            XElementIterator& operator=( const XElementIterator& other );
            XElementIterator& operator=( XElementIterator&& other ) = default;
            ~XElementIterator() = default;
            
            // STL Iterator Compliance
            typedef ptrdiff_t difference_type; // ???
            typedef XElement value_type;
            typedef XElement* pointer;
            typedef XElement& reference;
            typedef std::bidirectional_iterator_tag iterator_category;
            
            
            // Iterator operators
            bool operator==(const XElementIterator& rhs) const;
            bool operator!=(const XElementIterator& rhs) const;
            
            XElement& operator*() const;
            XElement* operator->() const;
            
            const XElementIterator& operator++();
            XElementIterator operator++(int);
            
            const XElementIterator& operator--();
            XElementIterator operator--(int);
            
            bool getIsPayloadNull() const;

            // Reveal the private data member, violates
            // encapsulation but could not find a better way
            const XElementIterImplUP& reveal() const;
            
        private:
            XElementIterImplUP myImpl;
        };
    }
}
