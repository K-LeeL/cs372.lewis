// Assignment 05, Part 1: An Exercise In the Use of Smart Pointers
// Due: Tue 10/3/2023
//
// File:   A5Part1.cpp
// Author: Kaylee Lewis

// Refactor the `List` class in your class library to use smart pointers
// instead of raw pointers. You will need to adjust the memory allocation and
// deallocation of nodes appropriately.
// Update your test cases and regression test the changes (i.e., make certain
// to run all tests),

//https://solarianprogrammer.com/2019/02/22/cpp-17-implementing-singly-linked-list-smart-pointers/

#include <iostream>

template< typename T >
class SmartList
{
private:
    struct Node
    {
        T data;
        std::weak_ptr< Node > prev;
        std::shared_ptr< Node > next;

        Node( T d ) : data( d )
        {
        }
    };

    std::shared_ptr< Node > head = nullptr;
    std::shared_ptr< Node > tail = nullptr;
    std::size_t length = 0;

public:
    SmartList( )
    {
    }

    SmartList( T newData )
    {
        auto newNode = std::make_shared< Node >( newData );
        head = newNode;
        tail = newNode;
        length++;
    }

    bool empty( ) const
    {
        return ( head == nullptr );
    }

    void push_front( T data )
    {
        auto newNode = std::make_shared< Node >( data );
        newNode->next = head;
        if( head )
        {
            head->prev = newNode;
        }
        head = newNode;
        if( !tail )
        {
            tail = head;
        }
        length++;
    }

    void push_back( T data )
    {
        auto newNode = std::make_shared< Node >( data );
        newNode->prev = tail;
        if( tail )
        {
            tail->next = newNode;
        }
        tail = newNode;
        if( !head )
        {
            head = tail;
        }
        length++;
    }

    void pop_front( )
    {
        if( empty( ) )
        {
            throw std::out_of_range( "pop_front(): Attempt to pop from empty list." );
        }
        head = head->next;
        if( head )
        {
            head->prev.reset( );
        }
        length--;
        if( head == nullptr )
        {
            tail = nullptr;
        }
    }

    void pop_back( )
    {
        if( empty( ) )
        {
            throw std::out_of_range( "pop_back(): Attempt to pop from empty list." );
        }
        if( tail )
        {
            tail->next.reset( );
        }
        length--;
        if( tail == nullptr )
        {
            head = nullptr;
        }
    }

    T &front( ) const
    {
        if( empty( ) )
        {
            throw std::out_of_range( "List is empty, cannot fetch front." );
        }
        return head->data;
    }

    T &back( ) const
    {
        if( empty( ) )
        {
            throw std::out_of_range( "List is empty, cannot fetch back." );
        }
        return tail->data;
    }

    void traverse( void ( *doIt )( T &data ) )
    {
        auto current = head;
        while( current != nullptr )
        {
            doIt( current->data );
            current = current->next;
        }
    }

    void insert( std::shared_ptr< Node > insertPoint, T d )
    {
        if( insertPoint == nullptr )
        {
            throw std::invalid_argument( "insertPoint cannot be nullptr" );
        }
        auto newNode = std::make_shared< Node >( d );

        auto current = head;
        while( current != nullptr && current != insertPoint )
        {
            current = current->next;
        }

        if( current == insertPoint )
        {
            newNode->prev = current->prev;
            newNode->next = current;
            if( current->prev.lock( ) )
            {
                current->prev.lock( )->next = newNode;
            } else
            {
                head = newNode;
            }
            current->prev = newNode;
            length++;
        } else
        {
            throw std::runtime_error( "insertPoint not found in the list" );
        }
    }

    class const_iterator
    {
    public:
        const_iterator( const_iterator &itr ) : current( itr.current.get( ) )
        {
        }

        T &operator*( ) const
        {
            return retrieve( );
        }

        const_iterator &operator++( )
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++( int )
        {
            const_iterator old = *this;
            ++( *this );
            return old;
        }

        bool operator==( const const_iterator &rhs ) const
        {
            return current == rhs.current;
        }

        bool operator!=( const const_iterator &rhs ) const
        {
            return !( *this == rhs );
        }

    protected:
        Node *current;

        T &retrieve( ) const
        {
            return current->data;
        }

    public:
        const_iterator( Node *p ) : current( p )
        {
        }
    };

    // Iterator added for test
    class iterator
    {
    public:
        iterator( ) : current( nullptr )
        {
        }

        T &operator*( )
        {
            return current->data;
        }

        iterator &operator++( )
        {
            current = current->next;
            return *this;
        }

        bool operator==( const iterator &rhs ) const
        {
            return current == rhs.current;
        }

        bool operator!=( const iterator &rhs ) const
        {
            return !( *this == rhs );
        }

        std::shared_ptr< Node > current;

        iterator( std::shared_ptr< Node > p ) : current( p )
        {
        }
    };

    iterator begin( )
    {
        return iterator{ head };
    }

    iterator end( )
    {
        return iterator{ nullptr };
    }

    const_iterator cbegin( ) const
    {
        return const_iterator{ head.get( ) };
    }

    const_iterator cend( ) const
    {
        return const_iterator{ nullptr };
    }

    iterator erase( iterator itr )
    {
        auto p = itr.current;
        auto toReturn = iterator{ p->next };
        if( p->prev.lock( ) )
        {
            p->prev.lock( )->next = p->next;
        }
        if( p->next )
        {
            p->next->prev = p->prev;
        }
        length--;
        return toReturn;
    }

    iterator insert( iterator itr, const T &x )
    {
        auto p = itr.current;
        auto newNode = std::make_shared< Node >( x );
        newNode->next = p;
        newNode->prev = p->prev;
        if( p->prev.lock( ) )
        {
            p->prev.lock( )->next = newNode;
        }
        p->prev = newNode;
        length++;
        return iterator{ newNode };
    }

    iterator erase( iterator from, iterator to )
    {
        iterator itr = from;
        while( itr != to )
        {
            itr = erase( itr );
        }
        return to;
    }

    // Compare two lists
    bool operator==( const SmartList &other ) const
    {
        if( length != other.length )
        {
            return false;
        }
        auto current = head;
        auto otherCurrent = other.head;
        while( current != nullptr && otherCurrent != nullptr )
        {
            if( current->data != otherCurrent->data )
            {
                return false;
            }
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        return true;
    }
};

void printElement( int &data )
{
    std::cout << data << " ";
}

int main( )
{
    SmartList< int > TestList;

    TestList.push_back( 1 );
    TestList.push_back( 3 );
    TestList.push_front( 0 );
    TestList.push_back( 2 );

    std::cout << "List after pushes: ";
    TestList.traverse( printElement );
    std::cout << std::endl;

    TestList.pop_back( );
    TestList.pop_front( );

    std::cout << "List after pops: ";
    TestList.traverse( printElement );
    std::cout << std::endl;

    std::cout << "Front: " << TestList.front( ) << std::endl;
    std::cout << "Back: " << TestList.back( ) << std::endl;

    std::cout << "List using iterators: ";
    for( auto it = TestList.begin( ) ; it != TestList.end( ) ; ++it )
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    auto it = TestList.begin( );
    ++it;  // Point to the second element
    TestList.erase( it );

    std::cout << "List after erase: ";
    TestList.traverse( printElement );
    std::cout << std::endl;


    return 0;
}
