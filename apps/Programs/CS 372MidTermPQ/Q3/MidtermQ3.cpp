// CS 372 Mid-term Exam: Programming Questions - Question 3
// Due: Tue Sep 19, 2023 10:00pm
//
// File:   MidtermQ3.cpp
// Author: Kaylee Lewis

// Question 3: People like to be lazy.   To the point at times where we try to write our code to be lazy as well.   
// For example, there is the concept of doing a "lazy deletion" from a linked list.   For "lazy deletion", we delay deleting the items from the list until some storage condition is met.   The deletion process just needs to mark an item as deleted and then delete anything marked as deleted when needed.   

// Modify the linked list class from our lectures to support lazy deletion.
// Keep track of the deleted status as an extra field in your node class and keep a count of deleted and not -deleted nodes as private state in your modifed linked list.
// Delete all deleted items from the list when the number of deleted items equals the number of non - deleted items
// (do this by traversing the list, deleting items as normal, and remember to keep the pointers straight).
// Modify all other methods in the class to correctly ignore deleted items.

//https://www.geeksforgeeks.org/deletion-in-linked-list/

#include <stdexcept>
#include <iostream>

template< typename T >
class List
{
private:
    class Node
    {
    public:
        T data;
        bool deleted;
        Node *prev;
        Node *next;

        Node( ) : deleted( false ), prev( nullptr ), next( nullptr )
        {
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;

    int nodesDeleted = 0;
    int nodesNotDeleted = 0;

    void setupList( )
    {
        Node *newNode = new Node( );
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode;
        tail = newNode;
    }

    void deleteListContents( )
    {
        Node *current = head;
        Node *temp = nullptr;
        while( current != nullptr )
        {
            temp = current->next;
            delete current;
            current = temp;
        }
    }

    void actualDeletion( )
    {
        Node *current = head;
        Node *temp = nullptr;
        while( current != nullptr )
        {
            if( current->deleted )
            {
              if (current->prev) current->prev->next = current->next;
              if (current->next) current->next->prev = current->prev;
              if (current == head) head = current->next;
              if (current == tail) tail = current->prev;

              temp = current;
              current = current->next;
              delete temp;
              nodesDeleted--;
            } else
            {
                current = current->next;
            }
            nodesNotDeleted -= nodesDeleted;
            nodesDeleted = 0;
        }
    }

public:
    List( ) = default;

    List( T newData )
    {
        setupList( );
        head->data = newData;
        nodesNotDeleted++;
    }

    List( List &rhs )
    {  // copy constructor
        deleteListContents( );
        head = rhs.head;
        tail = rhs.tail;
    }

    ~List( )
    {  // And a destructor
        deleteListContents( );
    }

    bool empty( )
    {
        return ( head == nullptr );
    }

    void push_front( T data )
    {
        if( this->empty( ) )
        {
            setupList( );
            head->data = data;
            tail = head;
        } else
        {
            Node *newNode = new Node( );
            newNode->data = data;
            newNode->next = head;
            newNode->prev = nullptr;
            head = newNode;
        }
        nodesNotDeleted++;

    }

    void push_back( T data )
    {
        if( this->empty( ) )
        {
            setupList( );
            head->data = data;
            tail = head;
        } else
        {
            Node *newNode = new Node( );
            newNode->data = data;
            newNode->next = nullptr;
            newNode->prev = tail;
            tail = newNode;
            nodesNotDeleted++;
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

    void pop_back( )
    {
        if( tail )
        {
            tail->deleted = true;
            nodesDeleted++;
            nodesNotDeleted--;
        }

        if( nodesDeleted == nodesNotDeleted )
        {
            actualDeletion( );
        }
    }

    void pop_front( )
    {
        if( head )
        {
            head->deleted = true;
            nodesDeleted++;
            nodesNotDeleted--;
        }

        if( nodesDeleted == nodesNotDeleted )
        {
            actualDeletion( );
        }

    }

    void traverse( void ( *doIt )( T data ) )
    {
        Node *current = head;
        while (current != nullptr) {
            if (!current->deleted) {
                doIt(current->data);
            }
            current = current->next;
        }
    }
};

    void print(int data) { std::cout << data << ' '; }

int main()
{
    List<int> List;

    List.push_front(1);
    List.push_front(2);
    List.push_front(3);
    List.push_front(4);
    List.push_front(5);

    std::cout << "List before any deletion: " << std::endl;
    List.traverse(print);
    std::cout << std::endl;

    List.pop_front();
    List.pop_back();

    std::cout << "List after lazy deletion (deleted nodes ignored): ";
    List.traverse(print);
    std::cout << std::endl;

    List.pop_front();
    List.pop_back();

    std::cout << "List after actual deletion (deleted nodes removed): ";
    List.traverse(print);
    std::cout << std::endl;

    return 0;
}