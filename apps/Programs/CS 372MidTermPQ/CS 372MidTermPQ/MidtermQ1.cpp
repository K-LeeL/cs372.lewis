// CS 372 Mid-term Exam: Programming Questions - Question 1
// Due: Tue Sep 19, 2023 10:00pm
//
// File:   MidtermQ1.cpp
// Author: Kaylee Lewis

// Question 1: Here's a another variation on the theme of lists:   self-adjusting list.
// Define a new template subclass of the List<> class named SelfAdjustingList<>  that adds one new method to the subclass:

// T* find(TitemToFind);

// Make the find() method do a linear search for the argument in the list.
// If it finds the item,  move it to the front of the list and then return a pointer to that item that is now in the front of the list.
// (NOTE: this is a rather common trick used to improve the search times on large lists.
// Over the time, the items you most often search for will be moved towards the front of the list)
//
//https://www.geeksforgeeks.org/self-organizing-list-move-front-method/

#include <iostream>
#include <vector>

template< typename T >
class List
{
public:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    int length = 0;

    void setupList( )
    {
        head = nullptr;
        tail = nullptr;
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

    void push_back( T data )
    {
        Node *newNode = new Node( );
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = tail;
        if (head == nullptr)
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

    void print()
    {
        Node *current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

template< typename T >
class SelfAdjustingList : public List< T >
{
public:
    T *find( T itemToFind )
    {
        typename List<T>::Node *current = this->head;
        typename List<T>::Node *prev = nullptr;

        while( current != nullptr )
        {
            if( current->data == itemToFind )
            {
                // If found move it to the front of hte list and then return a pointer to
                // the item that is now in the front

                if( prev != nullptr )
                {  
                    prev->next = current->next;
                    current->next = this->head;
                    this->head = current;
                }
                {
                    return &(current->data);
                }
            } else
            {
                prev = current;
                current = current->next;
            }
        }
        {
            return nullptr;
        }
    }
    void print()
    {
        List<T>::print();
    }
};

int main( )
{

    SelfAdjustingList<int> List;

    List.push_back(1);
    List.push_back(2);
    List.push_back(3);
    List.push_back(4);
    List.push_back(5);

    int *found = List.find(3);
    if (found != nullptr)
    {
        std::cout << "Found the item: " << *found << std::endl;
    }

    std::cout << "List after the item was found: ";
    List.print();
    
    return 0;
}
