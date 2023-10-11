// Assignment 06, Part 1: Generic Binary Search
// Due: Tue Oct 10, 2023 11:59pm
//
// File:   A6Part1.cpp
// Author: Kaylee Lewis

// Write a template function that implements a binary search of a vector of the template type, assuming the template type supports the relational operators
// (assume the argument contains a vector that is in sorted order.   Add an optional argument with default value of false that when the argument is set to true,
// prints the number of items you have to examine before either finding the search key or hitting end of the vector.

// The proptype of your function needs to be:
//   template <typename T>
//   bool binarySearch(vector<T> aSortedVector,  T itemToBeFound,  bool printDebugData = false);

// https://www.geeksforgeeks.org/binary-search-algorithms-the-c-standard-template-library-stl/

#include <iostream>
#include <vector>
#include "Header.h"

template <typename T>
bool binarySearch ( const std::vector<T> &aSortedVector , T itemToBeFound , bool printDebugData = false )
{
     int left = 0;
     int right = aSortedVector.size ( ) - 1;
     int mid;
     int count = 0;

     while ( left <= right )
     {
          count++;
          mid = left + ( right - left ) / 2;

          if ( aSortedVector [ mid ] == itemToBeFound )
          {
               if ( printDebugData )
               {
                    std::cout << "The number of items examined: " << count << std::endl;
               }
               return true;
          } else if ( aSortedVector [ mid ] < itemToBeFound )
          {
               left = mid + 1;
          } else
          {
               right = mid - 1;
          }
     }

     if ( printDebugData )
     {
          std::cout << "Number of items examined: " << count << std::endl;
     }
     return false;
}


int main ( )
{
     std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
     bool found = binarySearch ( vec , 5 , true );
     if ( found )
     {
          std::cout << "Found" << std::endl;
     } else
     {
          std::cout << "Not found" << std::endl;
     }

     return 0;
}
