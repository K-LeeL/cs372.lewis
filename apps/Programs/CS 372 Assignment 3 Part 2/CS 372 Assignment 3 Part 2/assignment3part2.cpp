// Assignment 03, Part 2: Switching the Bag To Use Lists
// Due: Tue Sep 5, 2023 11:59pm
//
// File:   assignment3part2.cpp
// Author: Kaylee Lewis
//
// Purpose:
//   Use the linked list class that you just built to create a second version
//   of the Bag class, replacing the vector class with your list class.
//
// test and set scripts from Dr. Lewis notes and includes
// https://learn.microsoft.com/en-us/cpp/standard-library/list?view=msvc-170
// https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-7.0
// https://learn.microsoft.com/en-us/cpp/standard-library/list-operators?view=msvc-170
// https://en.cppreference.com/w/cpp/container/list


#include <iostream>
#include "Library.h"
#include "Bag.h"
#include <set>


bool fncomp( int const lhs, int const rhs )
{
  return lhs < rhs;
};

struct classcomp
{
  bool operator()( const int &lhs, const int &rhs ) const
  {
    return lhs < rhs;
  }
};

// Function for test
void printItem( int &item )
{
  std::cout << item << " ";
}

int main( )
{
  // empty set of ints
  std::set< int > first;
  int myints[ ] = { 10, 20, 30, 40, 50 };

  // range
  std::set< int > second( myints, myints + 5 );

  // a copy of second
  std::set< int > third( second );

  // iterator ctor.
  std::set< int > fourth( second.begin( ), second.end( ) );

  // class as Compare
  std::set< int, classcomp > fifth;

  // function pointer as Compare
  bool ( *fn_pt )( int, int ) = fncomp;
  std::set< int, bool ( * )( int, int ) > sixth( fn_pt );

  // Create a ReceiptBag of floats
  ReceiptBag< float > receiptBag;

  // Insert items and get receipts
  ReceiptBag< float >::Receipt receiptId1 = receiptBag.insert( 3.14 );
  ReceiptBag< float >::Receipt receiptId2 = receiptBag.insert( 100000.0 );

  // Get the number of items in the ReceiptBag
  int const itemCount = receiptBag.size( );
  std::cout << "Number of items in the Bag: " << itemCount << std::endl;

  // Remove an item using the receipt
  float const removedItem = receiptBag.remove( receiptId1 );

  // Display the removed item if it's not 0.0
  if( removedItem != 0.0f )
  {
    std::cout << "Removed item from the Bag: " << removedItem << std::endl;
  }
  // Test
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

  return 0;
};
