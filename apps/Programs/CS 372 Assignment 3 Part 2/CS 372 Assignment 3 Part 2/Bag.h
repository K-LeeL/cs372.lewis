// Bag.h

#pragma once
#include <iostream>
#include "Library.h"

template< typename Thing >

class ReceiptBag
{
private:
  struct Node
  {
    Thing data;
    int receiptId;
    Node *next;

    Node( const Thing &item, int receipt ) : data( item ), receiptId( receipt ), next( nullptr )
    {
    }
  };

public:
  using Receipt = int;

  ReceiptBag( ) : nextReceipt( 1 ), head( nullptr ), bagSize( 0 )
  {
  }

  ~ReceiptBag( )
  {
    clear( );
  }

  // Insert an item into the bag and return a receipt
  Receipt insert( Thing aThing )
  {
    Node *newNode = new Node( aThing, nextReceipt++ );
    if( !head )
    {
      head = newNode;
    } else
    {
      Node *current = head;
      while( current->next )
      {
        current = current->next;
      }
      current->next = newNode;
    }
    ++bagSize;
    return newNode->receiptId;
  }

  // Remove an item using its receipt
  Thing remove( Receipt receiptId )
  {
    Node *current = head;
    Node *prev = nullptr;

    while( current )
    {
      if( current->receiptId == receiptId )
      {
        Thing removedThing = current->data;
        if( prev )
        {
          prev->next = current->next;
        } else
        {
          head = current->next;
        }
        delete current;
        --bagSize;
        return removedThing;
      }
      prev = current;
      current = current->next;
    }

    Thing emptyThing = Thing{ };
    std::cerr << "Invalid receipt. Item not found." << std::endl;
    return emptyThing;
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
    Node *current = head;
    while( current )
    {
      if( current->data == aThing )
      {
        bagCount++;
      }
      current = current->next;
    }
    return bagCount;
  }

  void clear( )
  {
    Node *current = head;
    while( current )
    {
      Node *nextNode = current->next;
      delete current;
      current = nextNode;
    }
    head = nullptr;
    bagSize = 0;
  }

private:
  Node *head;
  int bagSize;
  Receipt nextReceipt;
};

