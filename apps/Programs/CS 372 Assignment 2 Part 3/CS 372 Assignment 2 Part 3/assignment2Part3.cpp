// Assignment 02, Part 3: Bags With Receipts
// Due : Tue Aug 29, 2023 11 : 59pm
//
// File:   assignment2part3.cpp
// Author: Kaylee Lewis
//
// Purpose:
//   First-
//        Bag(): Create an empty bag.
//        insert(Thing aThing) pop()
//        Remove a Thing from the bag size()
//        Number of Things in the bag ? count(Thing aThing)
//        How many specific Things in the bag?
//
//   Second-
//        Adjust definition of 'Bag' class to a bag with receipts. 	
//        The insert function should return a unique integer known as a receipt.
//        On deletion, it must pass the remove function a copy of this receipt.
//        The function will remove the item matching the receipt and return a
//             reference to the removed item.
//        Implement the 'ReceiptBag' class and text scripts in the library
//
//   Code sources: Assembled from Dr. Lewis (My Glorious Instructor) vector.hpp, bag.hpp, bag.h, vector.h, and myvector.h
//   Test sources: Assembled from Dr. Lewis (My Glorious Instructor) stlmyvectest.cpp
// https://codereview.stackexchange.com/questions/260324/custom-vector-implementation-in-c
// https://www.geeksforgeeks.org/creating-a-vector-of-class-objects-in-cpp/
// https://www.geeksforgeeks.org/vector-in-cpp-stl/
// https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/
// https://www.geeksforgeeks.org/program-to-create-custom-vector-class-in-c/

#include <set>
#include "Bag.h"

bool fncomp( int const lhs, int const rhs )
{
    return lhs < rhs;
}

struct classcomp
{
    bool operator()( const int &lhs, const int &rhs ) const
    {
        return lhs < rhs;
    }
};

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
    ReceiptBag< float >::Receipt tape1 = receiptBag.insert( 3.14 );
    ReceiptBag< float >::Receipt tape2 = receiptBag.insert( 100000.0 );

    // Get the number of items in the ReceiptBag
    int const itemCount = receiptBag.size( );
    std::cout << "Number of items in the Bag: " << itemCount << std::endl;

    // Remove an item using the receipt
    float const removedItem = receiptBag.remove( tape1 );

    // Display the removed item if it's not 0.0
    if( removedItem != 0.0f )
    {
        std::cout << "Removed item from the Bag: " << removedItem << std::endl;
    }

    VecTester testing;
    std::cout << "Starting test: " << std::endl;
    testing.tester( );

    return 0;
}
