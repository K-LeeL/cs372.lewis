// Library.h
#pragma once

#include <iostream>

template< typename T >

class List
{
public:
    // Node for a linked list.
    struct Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node *prev = nullptr;
        bool deleted = false;

        Node( ) : data( T( ) ), next( nullptr ), prev( nullptr )
        {
        }

        Node
        ( const T &data_val, Node *next_val = nullptr, Node *prev_val = nullptr ) : data
            ( data_val ), next( next_val ), prev( prev_val )
        {
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    int length = 0;

public:
    List() : head(nullptr) {}
    // Add const_iterator for test
    class const_iterator
    {
    public:
        const_iterator( ) : current( nullptr )
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

        const_iterator( Node *p ) : current( p )
        {
        }

        friend class List< T >;
    };

    // Iterator added for test
    class iterator : public const_iterator
    {
    public:
        iterator( )
        {
        }

        T &operator*( )
        {
            return const_iterator::retrieve( );
        }

        const T &operator*( ) const
        {
            return const_iterator::operator*( );
        }

        iterator &operator++( )
        {
            this->current = const_iterator::current->next;
            return *this;
        }

        iterator operator++( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }

    protected:
        iterator( Node *p ) : const_iterator( p )
        {
        }

        friend class List< T >;
    };

private:
    void setupList( )
    {
        head = new Node( );
        tail = new Node( );
        head->next = tail;
        tail->prev = head;
        length = 0;
    }

    void deleteListContents( )
    {
        Node *current = head->next;
        Node *temp = nullptr;
        while( current != tail->prev )
        {
            temp = current->next;
            delete current;
            current = temp;
        }
    }

public:
    // Constructor: initialize an empty list

    List( T newData )
    {
        setupList( );
        push_back( newData );
    }

    List( const List &rhs )
    {
        setupList( );
        Node *current = rhs.head->next;
        while( current != rhs.tail )
        {
            push_back( current->data );
            current = current->next;
        }
    }

    // Destructor: clear the list.
    ~List( )
    {
        clear( );
        delete head;
        delete tail;
    }

    // Assignment Operator
    List &operator=( const List< T > &other )
    {
        if( this == &other )
        {
            return *this;
        }
        clear( );
        Node *current = other.head->next;
        while( current != other.tail )
        {
            push_back( current->data );
            current = current->next;
        }
        return *this;
    }

    // Check if the list is empty
    bool empty( ) const
    {
        return ( head->next == tail );
    }

    // begin and end added for test
    iterator begin( )
    {
        return iterator{ head->next };
    }

    iterator end( )
    {
        return iterator{ tail };
    }

    const_iterator cbegin( ) const
    {
        return const_iterator{ head->next };
    }

    const_iterator cend( ) const
    {
        return const_iterator{ tail };
    }

    iterator erase( iterator itr )
    {
        Node *p = itr.current;
        if( p == nullptr || p->next == nullptr || p->prev == nullptr )
        {
            // Handle the error, maybe throw an exception or return an end iterator
            throw std::runtime_error( "Invalid iterator for erase" );
        }
        iterator iterToReturn{ p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;  // deallocate memory
        return iterToReturn;
    }

    iterator insert( iterator itr, const T &x )
    {
        Node *p = itr.current;
        if( p == nullptr || p->prev == nullptr )
        {
            // Handle the error, maybe throw an exception or return an end iterator
            throw std::runtime_error( "Invalid iterator for insert" );
        }
        Node *newNode = new Node{ x, p->prev, p };
        p->prev->next = newNode;
        p->prev = newNode;
        length++;
        return iterator{ newNode };
    }


    // Add an element to the front of the list
    void push_front( T data )
    {
        Node *newNode = new Node( data, head->next, head );
        head->next->prev = newNode;
        head->next = newNode;
        length++;
    }

    // Add an element to the back of the list
    void push_back( T data )
    {
        Node *newNode = new Node( data, tail, tail->prev );
        tail->prev->next = newNode;
        tail->prev = newNode;
        length++;
    }

    const T &front( ) const
    {
        Node *actualHead = head->next;
        return actualHead->data;
    }

    const T &back( ) const
    {
        Node *actualTail = tail->prev;
        return actualTail->data;
    }

    // Remove the last element from the list
    void pop_back( )
    {
        if( !empty( ) )
        {
            Node *lastNode = tail->prev;
            tail->prev = lastNode->prev;
            lastNode->prev->next = tail;
            delete lastNode;
            length--;
        } else
        {
            throw std::runtime_error( "Attempt to pop from an empty list." );
        }
    }

    // Remove the first element from the list
    void pop_front( )
    {
        if( !empty( ) )
        {
            Node *firstNode = head->next;
            head->next = firstNode->next;
            Node *newFirstNode = head->next;
            newFirstNode->prev = head;
            delete firstNode;
            firstNode = nullptr;
            length--;
        } else
        {
            std::cerr << "pop_back(): Attempt to pop from empty list. " << std::endl;
        }
    }

    // Traverse the list and apply a function to each element
    void traverse( void ( *doIt )( T & ) )
    {
        Node *current = head->next;
        while( current != tail )
        {
            doIt( current->data );
            current = current->next;
        }
    }

    // Clear the list
    void clear( )
    {
        Node *current = head->next;
        Node *temp = nullptr;
        while( current != tail )
        {
            temp = current->next;
            delete current;
            current = temp;
        }
        head->next = tail;
        tail->prev = head;
        length = 0;
    }

    // Compare two lists
    bool operator==( const List &other ) const
    {
        if( length != other.length )
        {
            return false;
        }
        Node *current = head->next;
        Node *otherCurrent = other.head->next;
        while( current != tail && otherCurrent != other.tail )
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

    // Get the number of elements in the list
    int size( ) const
    {
        return length;
    }
};
