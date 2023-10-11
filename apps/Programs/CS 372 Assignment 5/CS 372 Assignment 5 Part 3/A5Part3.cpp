// Assignment 05, Part 3: Deleting nodes from a tree
// Due: Tue 10/3/2023
//
// File:   A5Part3.cpp
// Author: Kaylee Lewis

// We need to delete a node from a tree.  We provided the algorithm to do this
// in the lecture notes.   Implement this algorithm by adding a new method named
// delete to the tree class.   This function should take one parameter, the
// value stored in the node to be deleted passed as reference parameter.   If
// the method finds a node containing that value in the tree, delete it and
// return true.  Otherwise, return false to indicate the value was not found in
// the tree.

//https://www3.cs.stonybrook.edu/~youngkwon/cse214/Lecture10_Trees.pdf
//https://medium.com/@siddharthgupta555t/finally-understanding-recursion-and-binary-search-trees-857c85e72978

#include <iostream>
#include <functional>
#include "Header.h"

template< typename T >
class Tree
{
private:
     struct Node
     {
          T value;
          std::shared_ptr< Node > left;
          std::shared_ptr< Node > right;

          Node ( T v , std::shared_ptr< Node > l , std::shared_ptr< Node > r ) : value ( v ) , left ( l ) , right ( r )
          {
          }
     };

     explicit Tree ( std::shared_ptr< Node > &node ) : Root ( node )
     {
     }

     std::shared_ptr< Node > Root;

     bool deleteRec ( std::shared_ptr<Node> &node , const T &x )
     {
          if ( !node ) return false;

          if ( x < node->value )
          {
               return deleteRec ( node->left , x );
          } else if ( x > node->value )
          {
               return deleteRec ( node->right , x );
          } else
          {
               if ( !node->left )
               {
                    node = node->right;
               } else if ( !node->right )
               {
                    node = node->left;
               } else
               {
                    node->value = findAndRemoveMax ( node->left );
               }
               return true;
          }
     }

     T findAndRemoveMax ( std::shared_ptr<Node> &node )
     {
          if ( !node->right )
          {
               T maxValue = node->value;
               node = node->left;
               return maxValue;
          }
          return findAndRemoveMax ( node->right );
     }

public:
     Tree ( ) : Root ( )
     {
     }

     Tree ( Tree const &lft , T value , Tree const &rgt ) : Root ( std::make_shared< Node > ( value , lft.Root , rgt.Root ) )
     {
     }

     bool isEmpty ( ) const
     {
          return !Root;
     }

     T root ( ) const
     {
          if ( isEmpty ( ) )
          {
               throw std::out_of_range ( "Tree is empty" );
          }
          return Root->value;
     }

     Tree left ( ) const
     {
          if ( isEmpty ( ) )
          {
               return Tree ( );
          }
          return Tree ( Root->left );
     }

     Tree right ( ) const
     {
          if ( isEmpty ( ) )
          {
               return Tree ( );
          }
          return Tree ( Root->right );
     }

     bool member ( T x ) const
     {
          if ( isEmpty ( ) )
               return false;
          T y = root ( );
          if ( x < y )
               return left ( ).member ( x );
          else if ( y < x )
               return right ( ).member ( x );
          else
               return true;
     }

     bool isLeaf ( ) const
     {
          if ( isEmpty ( ) )
          {
               return false;
          }
          return !Root->left && !Root->right;
     }

     Tree insert ( T x ) const
     {
          if ( isEmpty ( ) )
               return Tree ( Tree ( ) , x , Tree ( ) );
          T y = root ( );
          if ( x < y )
               return Tree ( left ( ).insert ( x ) , y , right ( ) );
          else if ( y < x )
               return Tree ( left ( ) , y , right ( ).insert ( x ) );
          else
               return *this;  // no duplicates
     }

     bool deleteNode ( const T &x )
     {
          return deleteRec ( Root , x );
     }
};

void printElement ( const std::string &msg , bool value )
{
     std::cout << msg << ( value ? "true" : "false" ) << std::endl;
}

int main ( )
{
     Tree< int > t1;
     printElement ( "Is t1 empty? " , t1.isEmpty ( ) );

     Tree< int > t2 = t1.insert ( 5 );

     t2 = t2.insert ( 3 );
     t2 = t2.insert ( 7 );
     t2 = t2.insert ( 2 );

     printElement ( "Is 3 a member of t2? " , t2.member ( 3 ) );
     printElement ( "Is 7 a member of t2? " , t2.member ( 7 ) );
     printElement ( "Is 2 a member of t2? " , t2.member ( 2 ) );

     t2.deleteNode ( 7);
     t2.deleteNode ( 2 );

     printElement ( "Is 2 a member of t2 after deletion? " , t2.member ( 2 ) );

     t2.deleteNode ( 3 );

     printElement ( "Is 3 a member of t2 after deletion? " , t2.member ( 3 ) );

     t2.deleteNode ( 5 );

     printElement ( "Is 5 a member of t2 after deletion? " , t2.member ( 5 ) );

     return 0;
}