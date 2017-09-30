// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "../core/PositiveIntegerOrEmpty.h"
#include <string>
#include <sstream>
#include <memory>

namespace mx
{
    namespace core
    {
        
        class PositiveIntegerOrEmpty::impl
        {
        public:
            explicit impl()
            :myPositiveInteger( 1 )
            ,myIsEmpty( true )
            {}
            
            explicit impl( const PositiveInteger& value )
            :myPositiveInteger( value )
            ,myIsEmpty( false )
            {}
            
            explicit impl( const std::string& value )
            :myPositiveInteger( 1 )
            ,myIsEmpty( false )
            {
                parse( value );
            }
            
            bool getIsEmpty() const
            {
                return myIsEmpty;
            }
            bool getIsNumber() const
            {
                return ! myIsEmpty;
            }
            void setValueEmpty()
            {
                myPositiveInteger = PositiveInteger( 1 );
                myIsEmpty = true;;
            }
            void setValue( const PositiveInteger& value )
            {
                myPositiveInteger = PositiveInteger( value );
                myIsEmpty = false;
            }
            PositiveInteger getValueNumber() const
            {
                return myPositiveInteger;
            }
            void parse( const std::string& value )
            {
                if ( value == "" )
                {
                    myPositiveInteger = PositiveInteger( 1 );
                    myIsEmpty = true;
                }
                else
                {
                    /* if it contains only numeric
                     characters it must be a number */
                    myPositiveInteger.parse( value );
                    myIsEmpty = false;
                }
            }
        private:
            PositiveInteger myPositiveInteger;
            bool myIsEmpty;
        };
        
        
        PositiveIntegerOrEmpty::PositiveIntegerOrEmpty()
        :myImpl( new impl() )
        {}
        
        PositiveIntegerOrEmpty::PositiveIntegerOrEmpty( const PositiveInteger& value )
        :myImpl( new impl( value ) )
        {}
        
        PositiveIntegerOrEmpty::PositiveIntegerOrEmpty( const std::string& value )
        :myImpl( new impl( value ) )
        {}
        
        PositiveIntegerOrEmpty::~PositiveIntegerOrEmpty() {}
        
        PositiveIntegerOrEmpty::PositiveIntegerOrEmpty( const PositiveIntegerOrEmpty& other )
        :myImpl( new PositiveIntegerOrEmpty::impl( *other.myImpl ) )
        {}
        
        PositiveIntegerOrEmpty::PositiveIntegerOrEmpty( PositiveIntegerOrEmpty&& other )
        :myImpl( std::move( other.myImpl ) )
        {}
        
        PositiveIntegerOrEmpty& PositiveIntegerOrEmpty::operator=( PositiveIntegerOrEmpty&& other )
        {
            myImpl = std::move( other.myImpl );
            return *this;
        }
        
        PositiveIntegerOrEmpty& PositiveIntegerOrEmpty::operator=( const PositiveIntegerOrEmpty& other )
        {
            this->myImpl = std::unique_ptr<PositiveIntegerOrEmpty::impl>( new PositiveIntegerOrEmpty::impl( *other.myImpl ) );
            return *this;
        }
        
        bool PositiveIntegerOrEmpty::getIsEmpty() const
        {
            return myImpl->getIsEmpty();
        }
        bool PositiveIntegerOrEmpty::getIsNumber() const
        {
            return myImpl->getIsNumber();
        }
        void PositiveIntegerOrEmpty::setValueEmpty()
        {
            myImpl->setValueEmpty();
        }
        void PositiveIntegerOrEmpty::setValue( const PositiveInteger& value )
        {
            myImpl->setValue( value );
        }
        PositiveInteger PositiveIntegerOrEmpty::getValueNumber() const
        {
            return myImpl->getValueNumber();
        }
        
        void PositiveIntegerOrEmpty::parse( const std::string& value )
        {
            myImpl->parse( value );
        }
        
        std::string toString( const PositiveIntegerOrEmpty& value )
        {
            std::stringstream ss;
            toStream( ss, value );
            return ss.str();
        }
		std::ostream& toStream( std::ostream& os, const PositiveIntegerOrEmpty& value )
        {
            if ( value.getIsNumber() )
            {
                toStream( os, value.getValueNumber() );
            }
            else
            {
                ; // os << "";
            }
            return os;
        }
		std::ostream& operator<<( std::ostream& os, const PositiveIntegerOrEmpty& value )
        {
            return toStream( os, value );
        }
        
        
    }
}
