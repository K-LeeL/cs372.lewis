// Assignment 03, Part 4: Priority Lists
// Due: Tue Sep 5, 2023 11:59pm
//
// File:   assignment3part4.cpp
// Author: Kaylee Lewis
//
// Purpose:
// A priority list changes the definition of a list so that items are arranged in some numerical priority order.
// Build a new class that keeps an instance of your LIst class to store the list that keeps track of the priority
// value for each item (use a structure that is stored within the List instance).
// Modify the List class to include a insert method, that given a pointer to an insert point, inserts a new entry
// in a List right before the item pointed to by the pointer.
// Use this new function on the List class to insert as the way to insert items into the priority list at the correct
// location.
//
#include <iostream>
#include <stdexcept>
#include "Library.h"

// PriorityData definition
template< typename T >
struct PriorityData
{
public:
  T data = T( );
  int priority = 0;
  PriorityData() : data(T()), priority(0) {}
  PriorityData(T d, int p) : data(d), priority(p){}




    bool operator>(const PriorityData &other) const {
    return priority > other.priority;
  }
};

// PriorityList definition
template< typename T >
class PriorityList
{
private:
  List< PriorityData< T > > dataList;

public:
  PriorityList( )
  {
  }

  void insert( const T &data, int priority )
  {
    PriorityData< T > newData( data, priority );
    if( dataList.empty( ) )
    {
      dataList.push_front( newData );
      return;
    }
    auto it = dataList.begin( );
    while( it != dataList.end( ) && newData > *it )
    {
      ++it;
    }
    dataList.insert( it, newData );
  }

  void pop_highest( )
  {
    if( !dataList.empty( ) )
    {
      dataList.pop_front( );
    }
  }

  T highest( ) const
  {
    if( !dataList.empty( ) )
    {
      return dataList.front( ).data;
    }
    throw std::runtime_error( "The priority list is empty" );
  }
};

int main( )
{
  PriorityList< int > pList;
  pList.insert( 10, 1 );
  pList.insert( 20, 3 );
  pList.insert( 30, 2 );

  std::cout << "The highest-priority element is: " << pList.highest( ) << std::endl;

  pList.pop_highest( );

  std::cout << "The highest-priority element after pop is: " << pList.highest( ) << std::endl;

  return 0;
}
