// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../xml/XAttributeIterator.h"

namespace mx
{
    namespace xml
    {
        XAttributeIterator::XAttributeIterator()
        : myImpl( nullptr )
        {
            
        }
        
        
        XAttributeIterator::XAttributeIterator( const XAttributeIterImpl& impl )
        : myImpl( impl.clone() )
        {
            
        }
        
        
        XAttributeIterator::XAttributeIterator( const XAttributeIterator& other )
        : myImpl( nullptr )
        {
            if( other.myImpl )
            {
                myImpl = other.myImpl->clone();
            }
        }
        
        
        XAttributeIterator& XAttributeIterator::operator=( const XAttributeIterator& other )
        {
            if( other.myImpl )
            {
                myImpl = other.myImpl->clone();
            }
            return *this;
        }
        
        
        bool XAttributeIterator::operator==(const XAttributeIterator& rhs) const
        {
            if( !myImpl )
            {
                return false;
            }
            return myImpl->equals( rhs );
        }
        
        
        bool XAttributeIterator::operator!=(const XAttributeIterator& rhs) const
        {
            if( !myImpl )
            {
                return false;
            }
            return !myImpl->equals( rhs );
        }
        
        
        XAttribute& XAttributeIterator::operator*() const
        {
            if( !myImpl )
            {
                throw std::runtime_error( "XAttributeIterator::operator*() - null dereference attempted" );
            }
            return myImpl->getRef();
        }
        
        
        XAttribute* XAttributeIterator::operator->() const
        {
            if( !myImpl )
            {
                throw std::runtime_error( "XAttributeIterator::operator->() - null dereference attempted" );
            }
            return myImpl->getPtr();
        }
        
        
        const XAttributeIterator& XAttributeIterator::operator++()
        {
            if( myImpl )
            {
                myImpl->increment();
            }
            return *this;
        }
        
        
        XAttributeIterator XAttributeIterator::operator++(int)
        {
            if( !myImpl )
            {
                return XAttributeIterator{};
            }
            XAttributeIterImplUP temp = myImpl->clone();
            myImpl->increment();
            return XAttributeIterator{ *temp };
        }
        
        
        const XAttributeIterator& XAttributeIterator::operator--()
        {
            if( myImpl )
            {
                myImpl->decrement();
            }
            return *this;
        }
        
        
        XAttributeIterator XAttributeIterator::operator--(int)
        {
            if( !myImpl )
            {
                return XAttributeIterator{};
            }
            XAttributeIterImplUP temp = myImpl->clone();
            myImpl->decrement();
            return XAttributeIterator{ *temp };
        }
        
        
        const XAttributeIterImplUP& XAttributeIterator::reveal() const
        {
            return myImpl;
        }
    }
}
