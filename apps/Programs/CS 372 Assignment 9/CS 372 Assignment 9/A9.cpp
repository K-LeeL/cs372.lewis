// Assignment 09, Part 01: A Timing Thing
// Due: Tue Oct 31 , 2023 11 : 59pm
// 
// The C++ standard claims that sort() algorithm in the standard template library has performance equal to Quicksort in the average case.
//
// Let's test that by writing a template function version of Quicksort that will sort the contents of a vector of the template type.
//
// Then write a program that use the C++ STL chrono library ( as you did for the Towers of Hanoi problem at the start of semester )
// that randomly generates vectors of 100 , 500 , 1000 , 5000 , and 10000 integers , times how long it takes your Quicksort function
// to sort each vector and then times how long it takes the std::sort ( ) function from the STL algorithms library to sort the same
// vector.
// https://stackoverflow.com/questions/2105737/has-anyone-seen-this-improvement-to-quicksort-before
// https://codereview.stackexchange.com/questions/157064/fast-quicksort-implementation

#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

template <typename T>
T partition ( T a [ ] , int start , int end )
{
     int pivot = a [ end ];
     int pIndex = start;

     for ( int i = start; i < end; i++ )
     {
          if ( a [ i ] <= pivot )
          {
               std::swap ( a [ i ] , a [ pIndex ] );
               pIndex++;
          }
     }

     std::swap ( a [ pIndex ] , a [ end ] );

     return pIndex;
}

template <typename T>
void quickSort ( T arr [ ] , int low , int high )
{
     if ( low < high )
     {
          int s = partition ( arr , low , high );
          quickSort ( arr , low , s - 1 );
          quickSort ( arr , s + 1 , high );
     }
}

void iterativeQuicksort ( int a [ ] , int n )
{
     std::stack<std::pair<int , int>> s;
     int start = 0;
     int end = n - 1;
     s.push ( std::make_pair( start , end ) );

     while ( !s.empty ( ) )
     {
          start = s.top ( ).first , end = s.top ( ).second;
          s.pop ( );
          int pivot = partition ( a , start , end );

          if ( pivot - 1 > start )
          {
               s.push ( std::make_pair( start , pivot - 1 ) );
          }

          if ( pivot + 1 < end )
          {
               s.push ( std::make_pair( pivot + 1 , end ) );
          }
     }
}

template <typename T>
void generateRandom ( std::vector<T> &arr , int size )
{
     std::srand ( static_cast< unsigned int >( std::time ( nullptr ) ) );
     for ( int i = 0; i < size; i++ )
     {
          arr.push_back ( std::rand ( ) % 10000 + 1 );
     }
}

int main ( )
{
     std::vector<int> sizes = { 100, 500, 1000, 5000, 10000 };

     for ( int size : sizes )
     {
          std::vector<int> random_vector;
          generateRandom ( random_vector , size );

          auto start_time_quicksort = std::chrono::high_resolution_clock::now ( );
          quickSort ( random_vector.data ( ) , 0 , random_vector.size ( ) - 1 );
          auto end_time_quicksort = std::chrono::high_resolution_clock::now ( );

          std::chrono::duration<double , std::micro> duration_quicksort = end_time_quicksort - start_time_quicksort;

          std::cout << "Vector size: " << size << std::endl;
          std::cout << "Quicksort Time: " << duration_quicksort.count ( ) << " microseconds" << std::endl;
          std::cout << std::endl;
     }

     return 0;
}