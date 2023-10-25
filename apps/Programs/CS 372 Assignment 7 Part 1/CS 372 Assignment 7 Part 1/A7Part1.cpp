// CS 372 Assignment 7 Part 1: Making a graph
// Due: Tue Oct 24, 2023 11:59pm
//
// File: A7Part1.cpp
// Author: Kaylee Lewis
//
// Add an abstract base class for a graph,  an adjacency list graph class that inherits
// from that base class, and an adjacency matrix graph class to your class libary.
//

// https://www.programiz.com/dsa/graph-adjacency-matrix
// https://www.educative.io/courses/graph-algorithms-coding-interviews-c-plus-plus/adjacency-matrix
// https://www.geeksforgeeks.org/add-and-remove-vertex-in-adjacency-list-representation-of-graph/
// https://www.geeksforgeeks.org/add-and-remove-edge-in-adjacency-list-representation-of-a-graph/

#include <iostream>
#include "Header.h"

template <class N>
class Graph
{
public:
    // Default constuctor, create empty
     Graph ( ){}
     Graph ( Vector<N> nodes , Vector<std::pair<N , N>> edges ){}
     virtual ~Graph ( ){}

     virtual bool adjacent ( N x , N y ) = 0;
     virtual Vector<N> neighbors ( N x ) = 0;
     virtual void addNode ( N x ) = 0;
     virtual void addEdge ( N x , N y ) = 0;
     virtual void deleteEdge ( N x , N y ) = 0;
};

template <class N>
class AdjListGraph : public Graph<N>
{
private:
     using Edges = List<std::pair<int , int>>;
     Vector<N> nodes;
     Vector<List<N>> edges;
public:
     AdjListGraph ( ) : Graph<N> ( ){}
     AdjListGraph ( const AdjListGraph &other ) : Graph<N> ( ){}
     AdjListGraph &operator= ( const AdjListGraph &source )
     {
          return *this;
     }
     AdjListGraph ( Vector<N> newNodes , Vector<std::pair<N , N>> newEdges ) :
          Graph<N> ( newNodes , newEdges ){}
     ~AdjListGraph ( ){}

     virtual bool adjacent ( N x , N y ) override
     {
          for ( const auto &neighbor : neighbors ( x ) )
          {
               if ( neighbor == y )
               {
                    return true;
               }
          }
          return false;
     }
     virtual Vector<N> neighbors ( N x ) override
     {
          int index = -1;
          Vector<N> neighborVector;
          for ( int i = 0; i < nodes.size ( ); ++i )
          {
               if ( nodes.at ( i ) == x )
               {
                    index = i;
                    break;
               }
          }
          if ( index != -1 )
          {
               List<N> &neighborList = edges.at ( index );
               typename List<N>::Node *current = neighborList.head->next;
               while ( current != neighborList.tail )
               {
                    neighborVector.push_back ( current->data );
                    current = current->next;
               }
          }
          return neighborVector;
     }
     virtual void addNode ( N x ) override
     {
          nodes.push_back ( x );
          edges.push_back ( List<N> ( ) );
     }
     virtual void addEdge ( N x , N y ) override
     {
          int index = -1;
          for ( int i = 0; i < nodes.size ( ); ++i )
          {
               if ( nodes.at ( i ) == x )
               {
                    index = i;
                    break;
               }
          }
          if ( index != -1 )
          {
               edges.at ( index ).push_back ( y );  
          }
     }
     virtual void deleteEdge ( N x , N y ) override
     {
          int index = -1;
          for ( int i = 0; i < nodes.size ( ); ++i )
          {
               if ( nodes.at ( i ) == x )
               {
                    index = i;
                    break;
               }
          }
          if ( index != -1 )
          {
               List<N> &edgeList = edges.at ( index );
               typename List<N>::Node *current = edgeList.head->next;
               typename List<N>::Node *prev = edgeList.head;
               while ( current != edgeList.tail )
               {
                    if ( current->data == y )
                    {
                         prev->next = current->next;
                         current->next->prev = prev;
                         delete current;
                         break;
                    }
                    prev = current;
                    current = current->next;
               }
          }
     }
};

template <class N>
class AdjMatrixGraph : public Graph<N>
{
private:
     const static int MaxSize = 100;
     Vector<N> nodes;
     int adjMatrix [ MaxSize ] [ MaxSize ] = {};

public:
     AdjMatrixGraph ( ) : Graph<N> ( ){}
     AdjMatrixGraph ( const AdjMatrixGraph &other ) : Graph<N> ( ){}
     AdjMatrixGraph &operator= ( const AdjMatrixGraph &source ){}
     AdjMatrixGraph ( Vector<N> newNodes , Vector<std::pair<N , N>> newEdges ) :
          Graph<N> ( newNodes , newEdges ){}
     ~AdjMatrixGraph ( ){}

     int getIndex ( N node )
     {
          for ( int i = 0; i < nodes.size ( ); ++i )
          {
               if ( nodes.at ( i ) == node ) return i;
          }
          return -1;
     }
     virtual bool adjacent ( N x , N y ) override
     {
          int ix = getIndex ( x ) , iy = getIndex ( y );
          return ix != -1 && iy != -1 && adjMatrix [ ix ] [ iy ] == 1;
     }
     Vector<N> neighbors ( N x ) override
     {
          Vector<N> neighborVector;
          int ix = getIndex ( x );  // Get the index of node x
          if ( ix != -1 )
          {
               for ( int i = 0; i < nodes.size ( ); ++i )
               {
                    if ( adjMatrix [ ix ] [ i ] )
                    {
                         neighborVector.push_back ( nodes.at ( i ) );
                    }
               }
          }
          return neighborVector;
     }
     virtual void addNode ( N x ) override
     {
          nodes.push_back ( x );
     }
     virtual void addEdge ( N x , N y ) override
     {
          int ix = getIndex ( x ) , iy = getIndex ( y );
          if ( ix != -1 && iy != -1 )
          {
               adjMatrix [ ix ] [ iy ] = 1;
          }
     }
     virtual void deleteEdge ( N x , N y ) override
     {
          int ix = getIndex ( x ) , iy = getIndex ( y );
          if ( ix != -1 && iy != -1 )
          {
               adjMatrix [ ix ] [ iy ] = 0;
          }
     }
};

int main()
{
     AdjListGraph<int> adjListGraph;
     adjListGraph.addNode ( 1 );
     adjListGraph.addNode ( 2 );
     adjListGraph.addNode ( 3 );
     adjListGraph.addEdge ( 1 , 2 );
     adjListGraph.addEdge ( 1 , 3 );
     adjListGraph.addEdge ( 2 , 3 );

     std::cout << "In the list graph are 1 and 2 adjacent? " << ( adjListGraph.adjacent ( 1 , 2 ) ? "Yes" : "No" ) << std::endl;

     Vector<int> neighbors = adjListGraph.neighbors ( 1 );
     std::cout << "AdjListGraph: Neighbors of 1 are: ";
     for ( const auto &neighbor : neighbors )
     {
          std::cout << neighbor << " ";
     }
     std::cout << std::endl;

     adjListGraph.deleteEdge ( 1 , 2 );

     std::cout << "After deleting the edge in the list graph, are 1 and 2 adjacent? " << ( adjListGraph.adjacent ( 1 , 2 ) ? "Yes" : "No" ) << std::endl;
     std::cout << std::endl;

     AdjMatrixGraph<int> adjMatrixGraph;
     adjMatrixGraph.addNode ( 1 );
     adjMatrixGraph.addNode ( 2 );
     adjMatrixGraph.addNode ( 3 );
     adjMatrixGraph.addEdge ( 1 , 2 );
     adjMatrixGraph.addEdge ( 1 , 3 );
     adjMatrixGraph.addEdge ( 2 , 3 );

     std::cout << "In the matrix graph are 1 and 2 adjacent? " << ( adjMatrixGraph.adjacent ( 1 , 2 ) ? "Yes" : "No" ) << std::endl;

     neighbors = adjMatrixGraph.neighbors ( 1 );
     std::cout << "AdjMatrixGraph: Neighbors of 1 are: ";
     for ( const auto &neighbor : neighbors )
     {
          std::cout << neighbor << " ";
     }
     std::cout << std::endl;

     adjMatrixGraph.deleteEdge ( 1 , 2 );

     std::cout << "After deleting the edge in the matrix graph, are 1 and 2 adjacent? " << ( adjMatrixGraph.adjacent ( 1 , 2 ) ? "Yes" : "No" ) << std::endl;

     return 0;

}