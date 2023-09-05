// Assignment 03, Part 1 - Make A List
// Due: Tue Sep 5, 2023 11:59pm
//
// File:   assignment3part1.cpp
// Author: Kaylee Lewis
//
// Purpose:
//   Add the `ist class to the library, with any required test code to verify
//   they are operating correctly.
//
#pragma once

#include <iostream>

#include "Library.h"

template< typename T >

class List
{
private:
  // Node for a linked list.
  struct Node
  {
    T data;
    Node *next;
    Node *prev;

    Node( T val ) : data( val ), next( nullptr ), prev( nullptr )
    {
    }
  };

  Node *head;
  Node *tail;
  int length;

  // Iterator added for test
  class iterator
  {
  public:
    iterator( Node *node ) : current( node )
    {
    }

    iterator &operator++( )
    {
      current = current->next;
      return *this;
    }

    T &operator*( ) const
    {
      return current->data;
    }

    bool operator!=( const iterator &other ) const
    {
      return current != other.current;
    }

  private:
    Node *current;
  };


  // Add const_iterator for test
  class const_iterator
  {
  public:
    const_iterator( Node *node ) : current( node )
    {
    }

    const_iterator &operator++( )
    {
      current = current->next;
      return *this;
    }

    const T &operator*( ) const
    {
      return current->data;
    }

    bool operator!=( const const_iterator &other ) const
    {
      return current != other.current;
    }

  private:
    Node *current;
  };

public:
  // Constructor: initialize an empty list.
  List( ) : head( new Node( T( ) ) ), tail( new Node( T( ) ) ), length( 0 )
  {
    head->next = tail;
    tail->prev = head;
  }

  // begin and end added for test
  iterator begin( )
  {
    return iterator( head->next );
  }

  iterator end( )
  {
    return iterator( tail );
  }

  const_iterator cbegin( ) const
  {
    return const_iterator( head->next );
  }

  const_iterator cend( ) const
  {
    return const_iterator( tail );
  }

  // Copy Constructor
  List( const List< T > &other )
  {
    head = new Node( T( ) );
    tail = new Node( T( ) );
    head->next = tail;
    tail->prev = head;
    length = 0;
    Node *current = other.head->next;
    while( current != other.tail )
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

  // Add an element to the front of the list
  void push_front( T data )
  {
    Node *newNode = new Node( data );
    Node *actualHead = head->next;

    newNode->next = actualHead;
    actualHead->prev = newNode;

    head->next = newNode;
    newNode->prev = head;
    length++;
  }

  // Add an element to the back of the list
  void push_back( T data )
  {
    Node *newNode = new Node( data );
    Node *actualTail = tail->prev;

    newNode->prev = actualTail;
    actualTail->next = newNode;

    newNode->next = tail;
    tail->prev = newNode;
    length++;
  }

  // Get the first element in the list (front)
  T front( )
  {
    return head->next->data;
  }

  // Get the last element in the list (back)
  T back( )
  {
    return tail->prev->data;
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
      --length;
    } else
    {
      std::cerr << "Attempt to pop from empty list." << std::endl;
    }
  }

  // Remove the first element from the list
  void pop_front( )
  {
    if( !empty( ) )
    {
      Node *firstNode = head->next;
      head->next = firstNode->next;
      firstNode->next->prev = head;
      delete firstNode;
      --length;
    } else
    {
      std::cerr << "Attempt to pop from an empty list." << std::endl;
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
  bool operator==( List &other )
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

// Function for test
void printItem( int &item )
{
  std::cout << item << " ";
}

int main( )
{
  // Create a list
  List< int > myList;

  // Add some elements to the list
  myList.push_back( 1 );
  myList.push_back( 2 );
  myList.push_back( 3 );

  // Print the elements in the list
  std::cout << "The content of the list is:" << std::endl;
  myList.traverse( printItem );
  std::cout << std::endl;

  // Access elements by index
  std::cout << "The front element is: " << myList.front( ) << std::endl;

  // Remove the front element
  myList.pop_front( );

  // Check the size of the list
  std::cout << "The size of the list after pop is: " << myList.size( ) << std::endl;

  // Create another list and copy the contents
  List< int > anotherList;
  anotherList = myList;

  // Check if the two lists are equal
  if( myList == anotherList )
  {
    std::cout << "The lists are equal." << std::endl;
  } else
  {
    std::cout << "The lists are not equal." << std::endl;
  }

  // Clear the original list
  myList.clear( );

  // Check the size of the cleared list
  std::cout << "The cleared list size is: " << myList.size( ) << std::endl;

  //Test
  List< int > aListOfIntegers;
  if( aListOfIntegers.empty( ) )
  {
    std::cout << "Yep, the new list is empty. " << std::endl;
  }
  for( int i = 3 ; i >= 0 ; i-- )
  {
    aListOfIntegers.push_front( i );
  }
  aListOfIntegers.traverse( printItem );
  std::cout << std::endl;

  std::cout << "Test iterators: Mutable -> ";
  for( auto iter = aListOfIntegers.begin( ) ; iter != aListOfIntegers.end( ) ; ++iter )
  {
    std::cout << *iter << " ";
  }

  std::cout << "Test iterators: const -> ";
  for( auto iter = aListOfIntegers.cbegin( ) ; iter != aListOfIntegers.cend( ) ; ++iter )
  {
    std::cout << *iter << " ";
  }

  std::cout << std::endl;
  for( int i = 0 ; i < 3 ; i++ )
  {
    int datum = aListOfIntegers.back( );
    std::cout << datum << " ";
    aListOfIntegers.pop_back( );
  }
  std::cout << std::endl;
  if( !aListOfIntegers.empty( ) )
  {
    aListOfIntegers.traverse( printItem );
    std::cout << std::endl;
  }
  aListOfIntegers.push_back( 42 );
  aListOfIntegers.traverse( printItem );
  std::cout << std::endl;
}
