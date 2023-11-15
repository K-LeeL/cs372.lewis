// Exam 2 Programming Questions
// Question 1 :
// Assume that you have implemented the Tree class that we discussed in the lecture materials.    
// Write three functions that are not methods of the Tree class that provides information about a Tree
//        ( HINT : think traversal of a tree ) :
//     1. A function that , for a reference to the root of a Tree passed as a reference parameter , returns an integer value is the number of nodes in the Tree.
//     2. Write a function that counts the number of internal ( non - leaf ) nodes of the Tree whose root is passed a reference argument to the function.
//     3. The external path length of a tree is the sum of length of each path from a leaf to the root of a tree.
//             Write a recursive function to compute this value where your function will have two parameters :
//             a reference to the root of a tree , and a reference to integer summation value.
//             The body of your function should add 1 to the integer and then recursively call the function for both children.
//
#include <iostream>
#include <memory>

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

     explicit Tree ( std::shared_ptr<const Node > &node ) : Root ( node )
     {
     }

     std::shared_ptr<const Node > Root;

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

     std::shared_ptr<Node> getRoot ( )
     {
          return Root;
     }

};

// Function 1: Count the total number of nodes
template <typename T>
static int referenceFunction ( std::shared_ptr<typename Tree<T>::Node> node )
{
     if ( !node )
     {
          return 0;
     }
     return 1 + referenceFunction ( node->left ) + referenceFunction ( node->right );
}

// Function 2: Count the number of internal nodes
template <typename T>
static int internalFunction ( const std::shared_ptr<const typename Tree<T>::Node> &node )
{
     if ( !node || ( !node->left && !node->right ) )
     {
          return 0;
     }
     return 1 + internalFunction ( node->left ) + internalFunction ( node->right );
}

// Function 3: Calculate the external path length
template <typename T>
static void externalFunction ( std::shared_ptr<typename Tree<T>::Node> &node , int currentDepth , int &sum )
{
     if ( !node )
     {
          return;
     }
     if ( !node->left && !node->right )
     {
          sum += currentDepth;
     }
     externalFunction ( node->left , currentDepth + 1 , sum );
     externalFunction ( node->right , currentDepth + 1 , sum );
}

void printElement ( const std::string &msg , bool value )
{
     std::cout << msg << ( value ? "true" : "false" ) << std::endl;
}

int main ( )
{
     Tree<int> tree;
     tree.insert ( 10 );
     tree.insert ( 5 );
     tree.insert ( 15 );

     int totalNodes = referenceFunction ( tree.getRoot ( ) );
     std::cout << "Total number of nodes in the Tree: " << totalNodes << std::endl;

     int internalNodes = internalFunction ( tree.getRoot ( ) );
     std::cout << "Number of internal (non-leaf) nodes in the Tree: " << internalNodes << std::endl;

     int pathLength = 0;
     externalFunction ( tree.getRoot ( ) , 0 , pathLength );
     std::cout << "External path length of the Tree: " << pathLength << std::endl;

     return 0;
}