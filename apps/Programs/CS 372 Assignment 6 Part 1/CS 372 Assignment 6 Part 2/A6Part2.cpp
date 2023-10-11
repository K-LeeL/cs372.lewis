// Assignment 06, Part 2: Trees as part of structures and functions
// Due: Tue Oct 10, 2023 11:59pm
//
// File:   A6Part2.cpp
// Author: Kaylee Lewis

// Define a structure in C++ that has three fields:
// (1) a size t field that says how many of elements are in the next two fields,
// (2) a pointer to a dynamically allocated vector of integers containing that many elements, and
// (3) a pointer to a Tree object containing a binary search tree with the contents of that array.
// (NOTE: This will be a really big structure in memory.)
//
// Write a function in C++ that returns a pointer to one of these structures with a single parameter
// that says how many items are to be put into vector and tree.The function should fill the vect in
// the structure to be returned with random integers which you then sort ( use the STL’s sort function
// from the algorithms library ) and then insert those integers into the Tree indicated by the reference
// in the structure.

// https://codereview.stackexchange.com/questions/235220/binary-search-tree-using-templates-in-c

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "Header.h"

template <typename T>
class Tree;

struct BigStruct
{
     size_t size;
     Vector<int> *vect;
     Tree<int> *tree;

     BigStruct ( size_t s ) : size ( s ) , vect ( new Vector<int> ( ) ) , tree ( new Tree<int> ( ) )
     {
     }
     ~BigStruct ( )
     {
          delete vect;
          delete tree;
     }
};

BigStruct*createBigStruct ( size_t n)
{
     BigStruct *struc = new BigStruct ( n );
     for ( size_t i = 0; i < n; ++i )
     {
          int random_val = rand ( );
          struc->vect->push_back ( random_val );
     }
     std::sort ( struc->vect->begin ( ) , struc->vect->end ( ) );

     for ( size_t i = 0; i < n; ++i )
     {
          struc->tree->insert ( struc->vect->at ( i ) );
     }

     return struc;
}

     
int main ( )
{
     size_t n = 10; 
     BigStruct *bs = createBigStruct (n);

     std::cout << "Sorted vector values: " << std::endl;

     for ( size_t i = 0; i < n; ++i )
     {
          std::cout << bs->vect->at( i ) << std::endl;
     }
          std::cout << "Checking tree membership for some values: " << std::endl;
          for ( int val : {5 , 100 , 250 , 500} )
          {
               std::cout << "Is " << val << " in the tree? "
                    << ( bs->tree->member ( val ) ? "Yes" : "No" ) << std::endl;
          }
          delete bs;

     return 0;
}
