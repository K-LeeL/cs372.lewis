// CS 372 Assignment 7 Part 2: Your Social Graph
// Due: Tue Oct 24, 2023 11:59pm
//
// File: A7Part2.cpp
// Author: Kaylee Lewis
//
// Social networking applications use one form of a graph to keep track of your connections.
// This is a social graph. Have you heard of the parlor game "Seven Degrees of Kevin Bacon".
// In the game , if you start with a bunch of friends , it will take you no more than 7 tries to
// find a path in your social graph that will lead you to Kevin Bacon.
// Build a social graph for a group of 20 people including both you and Kevin Bacon.
// Write a function that given a reference to that social graph , tells you whether or not
// you are connected to Kevin Bacon.
// The function true if you are and also use a reference parameter to return a list that shows
// the path between you and Kevin Bacon if it exists or an empty list if it doesn't.
// ( Name dropping time : my Kevin Bacon number is two as I have two classmates from college
// who have worked on a film with Kevin Bacon ).
// 
// https://www.geeksforgeeks.org/add-and-remove-edge-in-adjacency-list-representation-of-a-graph/
// https://www.boost.org/doc/libs/1_77_0/libs/graph/doc/kevin_bacon.html
// https://en.cppreference.com/w/cpp/container/unordered_map
// https://cs.smu.ca/~porter/csc/ref/boost/programs/graph/bacon/kevin-bacon.cpp2html

#include <iostream>
#include "Header.h"
#include <queue>
#include <unordered_map>
#include <string>

bool isConnectedToKevinBacon ( AdjListGraph<std::string> &socialGraph , const std::string &startNode , Vector<std::string> &path )
{
     std::queue<std::string> toExplore;
     std::queue<int> levels; 
     std::unordered_map<std::string , std::string> cameFrom;
     toExplore.push ( startNode );
     levels.push ( 0 );
     cameFrom [ startNode ] = "";

     while ( !toExplore.empty ( ) )
     {
          std::string current = toExplore.front ( );
          int currentLevel = levels.front ( );
          toExplore.pop ( );
          levels.pop ( );

          if ( current == "Kevin Bacon" )
          {
               while ( current != "" )
               {
                    path.push_back ( current );
                    current = cameFrom [ current ];
               }
               return true;
          }

          if ( currentLevel >= 7 )
          {
               break;
          }

          for ( const auto &neighbor : socialGraph.neighbors ( current ) )
          {
               if ( cameFrom.find ( neighbor ) == cameFrom.end ( ) )
               {
                    toExplore.push ( neighbor );
                    levels.push ( currentLevel + 1 ); 
                    cameFrom [ neighbor ] = current;
               }
          }
     }

     return false;
}

int main ( )
{
     // 20 People including you and Kevin Bacon
     AdjListGraph<std::string> socialGraph;

     socialGraph.addNode ( "Kaylee" );
     socialGraph.addNode ( "Kelsey" );
     socialGraph.addNode ( "Hennis" );
     socialGraph.addNode ( "Socky" );
     socialGraph.addNode ( "Eclipse" );
     socialGraph.addNode ( "Dee" );
     socialGraph.addNode ( "Isaac" );
     socialGraph.addNode ( "Katie" );
     socialGraph.addNode ( "Andrew" );
     socialGraph.addNode ( "Derek" );
     socialGraph.addNode ( "Natasha" );
     socialGraph.addNode ( "Rueben" );
     socialGraph.addNode ( "Matt" );
     socialGraph.addNode ( "Micah" );
     socialGraph.addNode ( "Mara" );
     socialGraph.addNode ( "Sarah" );
     socialGraph.addNode ( "Bethany" );
     socialGraph.addNode ( "Jeff" );
     socialGraph.addNode ( "Brian" );
     socialGraph.addNode ( "David" );

     socialGraph.addNode ( "Kevin Bacon" );

     socialGraph.addEdge ( "Kelsey" , "Kaylee" );
     socialGraph.addEdge ( "Kaylee" , "Kelsey" );

     socialGraph.addEdge ( "Kaylee" , "Dee" );
     socialGraph.addEdge ( "Dee" , "Kaylee" );

     socialGraph.addEdge ( "Dee" , "Isaac" );
     socialGraph.addEdge ( "Isaac" , "Dee" );

     socialGraph.addEdge ( "Sarah" , "Jeff" );
     socialGraph.addEdge ( "Jeff" , "Sarah" );

     socialGraph.addEdge ( "Jeff" , "Kaylee" );
     socialGraph.addEdge ( "Kaylee" , "Jeff" );

     socialGraph.addEdge ( "Jeff" , "Brian" );
     socialGraph.addEdge ( "Brian" , "Jeff" );

     socialGraph.addEdge ( "Brian" , "Mara" );
     socialGraph.addEdge ( "Mara" , "Brian" );

     socialGraph.addEdge ( "Mara" , "Natasha" );
     socialGraph.addEdge ( "Natasha" , "Mara" );

     socialGraph.addEdge ( "Natasha" , "Kevin Bacon" );
     socialGraph.addEdge ( "Kevin Bacon" , "Natasha" );

     // Find whether you are connected to Kevin Bacon within 7 degrees
     Vector<std::string> path;
     bool connected = isConnectedToKevinBacon ( socialGraph , "Kaylee" , path );

     if ( connected )
     {
          std::cout << "Kaylee is connected to Kevin Bacon! The path is: ";
          for ( const auto &person : path )
          {
               std::cout << person << " -> ";
          }
          std::cout << std::endl;
     } else
     {
          std::cout << "Kaylee is not connected to Kevin Bacon within 7 degrees." << std::endl;
     }

     return 0;
}

