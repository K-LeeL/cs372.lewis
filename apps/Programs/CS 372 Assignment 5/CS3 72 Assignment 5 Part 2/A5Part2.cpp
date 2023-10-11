// Assignment 05, Part 2: Building a Tree
// Due: Tue 10/3/2023
//
// File:   A5Part2.cpp
// Author: Kaylee Lewis

// The lecture notes discuss a way to build a Tree class using smart pointers.
// Add this class to your class library.

//https://www3.cs.stonybrook.edu/~youngkwon/cse214/Lecture10_Trees.pdf

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

        Node( T v, std::shared_ptr< Node > l, std::shared_ptr< Node > r ) : value( v ), left( l ), right( r )
        {
        }
    };

    explicit Tree( std::shared_ptr< Node > &node ) : Root( node )
    {
    }

    std::shared_ptr< Node > Root;

public:
    Tree( ) : Root( )
    {
    }

    Tree( Tree const &lft, T value, Tree const &rgt ) : Root( std::make_shared< Node >( value, lft.Root, rgt.Root ) )
    {
    }

    bool isEmpty( ) const
    {
        return !Root;
    }

    T root( ) const
    {
        if( isEmpty( ) )
        {
            throw std::out_of_range( "Tree is empty" );
        }
        return Root->value;
    }

    Tree left( ) const
    {
        if( isEmpty( ) )
        {
            return Tree( );
        }
        return Tree( Root->left );
    }

    Tree right( ) const
    {
        if( isEmpty( ) )
        {
            return Tree( );
        }
        return Tree( Root->right );
    }

    bool member( T x ) const
    {
        if( isEmpty( ) )
            return false;
        T y = root( );
        if( x < y )
            return left( ).member( x );
        else if( y < x )
            return right( ).member( x );
        else
            return true;
    }

    bool isLeaf( ) const
    {
        if( isEmpty( ) )
        {
            return false;
        }
        return !Root->left && !Root->right;
    }

    Tree insert( T x ) const
    {
        if( isEmpty( ) )
            return Tree( Tree( ), x, Tree( ) );
        T y = root( );
        if( x < y )
            return Tree( left( ).insert( x ), y, right( ) );
        else if( y < x )
            return Tree( left( ), y, right( ).insert( x ) );
        else
            return *this;  // no duplicates
    }
};

void printElement( const std::string &msg, bool value )
{
    std::cout << msg << ( value ? "true" : "false" ) << std::endl;
}

int main( )
{
    Tree< int > t1;
    printElement( "Is t1 empty? ", t1.isEmpty( ) );

    Tree< int > t2 = t1.insert( 5 );
    printElement( "Is t2 empty? ", t2.isEmpty( ) );
    printElement( "Is 5 a member of t2? ", t2.member( 5 ) );
    printElement( "Is 6 a member of t2? ", t2.member( 6 ) );
    printElement( "Is t2 a leaf? ", t2.isLeaf( ) );

    Tree< int > t3 = t2.insert( 3 );
    Tree< int > t4 = t3.insert( 7 );

    printElement( "Is t4 a leaf? ", t4.isLeaf( ) );

    Tree< int > leftSubtree = t4.left( );
    printElement( "Is left subtree a leaf? ", leftSubtree.isLeaf( ) );

    Tree< int > rightSubtree = t4.right( );
    printElement( "Is right subtree a leaf? ", rightSubtree.isLeaf( ) );

    return 0;
}
