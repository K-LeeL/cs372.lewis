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
    public:
        T data;
        Node *next;
        Node *prev;
        bool isHiddenNode = false;

    };

    Node *head;
    Node *tail;
    int length;

public:

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
        Node *newNode = new Node( );
        newNode->next = tail;
        newNode->prev = head;
        head->next = newNode;
        tail->prev = newNode;
    }

    void deleteListContents( )
    {
        Node *current = head->next;
        while( current != tail )
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
        head->next = tail;
        tail->prev = head;
    }

public:
    // Constructor: initialize an empty list.
    List( )
    {
        head = new Node( );
        head->isHiddenNode = true;
        tail = new Node( );
        tail->isHiddenNode = true;
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
        length = 0;
    }

    List( T newData )
    {
        setupList( );
        ( head->next )->data = newData;
    }

    List( List &rhs )
    {
        // copy constructor
        deleteListContents( );
        head = rhs.head;
        tail = rhs.tail;
    }

    // Destructor: clear the list.
    ~List( )
    {
        deleteListContents( );
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
        iterator iterToReturn{ p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        return iterToReturn;
    }

    iterator insert( iterator itr, const T &x )
    {
        Node *p = itr.current;
        Node *newNode = new Node{ x, p->prev, p };
        p->prev->next = newNode;
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

    // Add an element to the front of the list
    void push_front( T data )
    {
        if( this->empty( ) )
        {
            setupList( );
            Node *actualHead = head->next;
            actualHead->data = data;
        } else
        {
            Node *actualHead = head->next;
            Node *newNode = new Node( );
            newNode->data = data;
            newNode->next = actualHead;
            actualHead->prev = newNode;
            newNode->prev = head;
            head->next = newNode;
        }
    }

    // Add an element to the back of the list
    void push_back( T data )
    {
        if( this->empty( ) )
        {
            setupList( );
            Node *actualTail = tail->prev;
            actualTail->data = data;
        } else
        {
            Node *actualTail = tail->prev;
            Node *newNode = new Node( );
            newNode->data = data;
            newNode->prev = actualTail;
            actualTail->next = newNode;
            newNode->next = tail;
            tail->prev = newNode;
        }
    }

    // Get the first element in the list (front)
    T front( )
    {
        Node *actualHead = head->next;
        return ( actualHead->data );
    }

    // Get the last element in the list (back)
    T back( )
    {
        Node *actualTail = tail->prev;
        return ( actualTail->data );
    }

    // Remove the last element from the list
    void pop_back( )
    {
        if( !empty( ) )
        {
            Node *lastNode = tail->prev;
            tail->prev = lastNode->prev;
            Node *newLastNode = tail->prev;
            newLastNode->next = tail;
            delete lastNode;
            lastNode = nullptr;
            length--;
        } else
        {
            std::cerr << "pop_back(): Attempt to pop from empty list. " << std::endl;
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
        while( !empty( ) )
        {
            pop_front( );
        }
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


