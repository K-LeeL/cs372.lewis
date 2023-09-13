// Library.h
#pragma once

#include <iostream>

template< typename T >

class List
{
private:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
        int priority;
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    int length = 0;

    void setupList( )
    {
        head = nullptr;
        tail = nullptr;
    }

    void deleteListContents( )
    {
        Node *temp = nullptr;
        Node *current = head;
        while( current != nullptr )
        {
            temp = current->next;
            delete current;
            current = temp;
        }
    }

public:
    List( ) : head( nullptr ), tail( nullptr )
    {
        setupList( );
    }

    List( T newData )
    {
        setupList( );
        head->data = newData;
    }

    List( const List &rhs )
    {
        setupList( );
        Node *current = rhs.head->next;
        while( current != nullptr )
        {
            push_back( current->data );
            current = current->next;
        }
    }

    ~List( )
    {
        deleteListContents( );
    }

    bool empty( )
    {
        return ( head == nullptr );
    }

    void push_front( T data, int p )
    {
        Node *newNode = new Node( );
        newNode->data = data;
        newNode->priority = p;
        newNode->next = head;
        newNode->prev = nullptr;
        if( empty( ) )
        {
            head = newNode;
            tail = newNode;
        } else
        {
            head->prev = newNode;
            head = newNode;
        }
    }

    void push_back( T data )
    {
        Node *newNode = new Node( );
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = tail;
        if( empty( ) )
        {
            tail = newNode;
            head = newNode;
        } else
        {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void pop_front( )
    {
        if( head->next == nullptr )
        {
            std::cerr << "pop_front(): Attempt to pop from empty list." << std::endl;
            return;
        }

        Node *firstNode = head->next;

        head->next = firstNode->next;

        if( head->next != nullptr )
        {
            head->next->prev = head;
        } else
        {
            tail = head;
        }

        delete firstNode;
        length--;
    }

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
        } else
        {
            std::cerr << "pop_back(): Attempt to pop from empty list. " << std::endl;
        }
    }

    T &front( )
    {
        if( head->next == nullptr )
        {
            throw std::out_of_range( "List is empty, cannot fetch front." );
        }
        return head->next->data;
    }

    T &back( )
    {
        Node *actualTail = tail->prev;
        return ( actualTail->data );
    }


    void traverse( void ( *doIt )( T &data ) )
    {
        Node *current = head;
        while( current != nullptr )
        {
            doIt( current->data );
            current = current->next;
        }
    }

    void insert( Node *insertPoint, T d, int p )
    {
        if( insertPoint == nullptr )
        {
            throw std::invalid_argument( "insertPoint cannot be nullptr" );
        }
        Node *current = head;
        Node *newNode = new Node( );
        newNode->data = d;
        newNode->priority = p;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if( head->priority > p )
        {
            push_front( d, p );
            return;
        }
        while( current->next != nullptr && current != insertPoint )
        {
            current = current->next;
        }
        if( current == insertPoint )
        {
            if( current->prev != nullptr )
            {
                current->prev->next = newNode;
            } else
            {
                // newNode is becoming the new head of the list.
                head = newNode;
            }
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev = newNode;
            length++;
        } else
        {
            throw std::runtime_error( "insertPoint not found in the list" );
        }
    }

    void priorityInsert( T d, int p )
    {
        Node *newNode = new Node( );
        newNode->data = d;
        newNode->priority = p;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if( head->next == nullptr )
        {
            head->next = newNode;
            newNode->prev = head;
            tail = newNode;
        } else
        {
            Node *current = head;
            while( current->next != nullptr && current->next->priority <= p )
            {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            if( current->next != nullptr )
            {
                current->next->prev = newNode;
            }
            current->next = newNode;
        }
        length++;
    }

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

    public:
        T *operator->( )
        {
            return &( this->current->data );
        }

    protected:
        iterator( Node *p ) : const_iterator( p )
        {
        }

        friend class List< T >;
    };

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
        iterator toReturn{ p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        length--;
        return toReturn;
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

    iterator findPriority( int priority )
    {
        for( auto it = begin( ) ; it != end( ) ; ++it )
        {
            if( it->priority > priority )
            {
                return it;
            }
        }
        return end( );
    }
};
