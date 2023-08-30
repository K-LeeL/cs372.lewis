// Bag.h

#pragma once
#include <iostream>
#include "vector.h"

#include <chrono>

const int PrintInterval = 10;

template< typename Thing >

class ReceiptBag
{
public:
    using Receipt = int;

    // Insert an item into the bag and return a receipt
    Receipt insert( Thing aThing )
    {
        bagContents.push_back( aThing );
        bagSize++;
        Receipt const tape = nextReceipt++;
        receiptTape.push_back( bagSize - 1 );
        return tape;
    }

    // Remove an item using its receipt
    Thing &remove( Receipt const tape )
    {
        int const toRemove = findReceipt( tape );

        if( toRemove != -1 )
        {
            // Grab the item to remove
            Thing &removedThing = bagContents[ receiptTape[ toRemove ] ];
            updateReceiptTape( toRemove );
            bagSize--;
            return removedThing;
        } else
        {
            static Thing emptyThing;
            std::cerr << "Invalid receipt. Item not found." << std::endl;
            return emptyThing;
        }
    }

    // Get the size of the bag
    int size( ) const
    {
        return bagSize;
    }

    // Count the occurrences of a specific item in the bag
    int count( Thing aThing )
    {
        int bagCount = 0;
        for( int i = 0 ; i < receiptTape.size( ) ; i++ )
        {
            // Compare with the stored items
            if( bagContents[ receiptTape[ i ] ] == aThing )
            {
                bagCount++;
            }
        }
        return bagCount;
    }

private:
    // Store the actual items
    vector< Thing > bagContents;

    // Store indices corresponding to receipts
    vector< int > receiptTape;
    int bagSize = 0;
    Receipt nextReceipt = 1;

    // Find the index in receiptTape corresponding to a receipt
    int findReceipt( Receipt tape )
    {
        for( int i = 0 ; i < receiptTape.size( ) ; i++ )
        {
            // Compare with stored receipts
            if( receiptTape[ i ] == tape )
            {
                return i;
            }
        }
        return -1;
    }

    // Update receiptTape after removing an item
    void updateReceiptTape( int removedIndex )
    {
        for( int i = removedIndex ; i < receiptTape.size( ) - 1 ; i++ )
        {
            receiptTape[ i ] = receiptTape[ i + 1 ];
        }
    }
};

// Vector Test
class VecTester
{
private:
    vector< int > testVector = vector< int >( );

    void fillVector( size_t cap )
    {
        for( int i = 0 ; i < cap ; ++i )
        {
            testVector.push_back( i );
        }
    }

public:
    void tester( )
    {
        size_t currentCap = testVector.capacity( );
        std::cout << "Starting capacity: " << currentCap << std::endl;
        for( int i = 0 ; i <= 500 ; i++ )
        {
            if( ( i % PrintInterval ) == 0 )
            {
                std::cout << "Current cap: " << currentCap << std::endl;
            }
            auto start = std::chrono::steady_clock::now( );
            testVector.push_back( i );
            auto end = std::chrono::steady_clock::now( );
            currentCap = testVector.capacity( );
            std::chrono::duration< double > elaspedSeconds = end - start;
            if( ( i % PrintInterval ) == 0 )
            {
                std::cout << "For increase capacity to " << currentCap << " took " << elaspedSeconds.count( ) <<
                    " seconds" << std::endl;
            }
        }
    }
};

