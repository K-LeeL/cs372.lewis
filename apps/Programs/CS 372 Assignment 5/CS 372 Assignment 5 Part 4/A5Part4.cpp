// Assignment 05: Part 4: Pruning a tree
// Due: Tue 10/3/2023
//
// File:   A5Part4.cpp
// Author: Kaylee Lewis

// This is an exercise in recursion: Write a standalone function (that is, a
// function that is not a method function of the tree class),  that when given a
// reference to a tree, returns a reference to a new tree that is almost a copy
// of the original tree except the new tree contains none of the leaves of the
// original tree.

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

  //Standalone function

template<typename T>
Tree<T> removeLeaves ( const Tree<T> &original )
{
     if ( original.isEmpty ( ) )
     {
          return Tree<T> ( );
     }

     if ( original.isLeaf ( ) )
     {
          return Tree<T> ( );
     }

     return Tree<T> ( removeLeaves ( original.left ( ) ) , original.root ( ) , removeLeaves ( original.right ( ) ) );
}

int main ( )
{
     Tree<int> t;
     t = t.insert ( 10 );
     t = t.insert ( 5 );
     t = t.insert ( 15 );
     t = t.insert ( 3 );
     t = t.insert ( 7 );

     Tree<int> result = removeLeaves ( t );

     std::cout << "Is 10 a member? " << ( result.member ( 10 ) ? "Yes" : "No" ) << std::endl;
     std::cout << "Is 5 a member? " << ( result.member ( 5 ) ? "Yes" : "No" ) << std::endl;
     std::cout << "Is 3 a member? " << ( result.member ( 3 ) ? "Yes" : "No" ) << std::endl;
     std::cout << "Is 7 a member? " << ( result.member ( 7 ) ? "Yes" : "No" ) << std::endl;

     return 0;
}