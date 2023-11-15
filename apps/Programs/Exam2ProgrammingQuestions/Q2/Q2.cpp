// Exam 2 Programming Questions
// Question 2 :
// Define a template function that "partitions" an STL list.
// The function should have three arugments: a "splitting value" whose type is the template, a list to be "partitioned",
// a pointer to a list of the template type containing all values less than the "splitting value",
// and a pointer to a list of the template type that is "greater than" the splitting value.
// Then use this function as a helper function for a function that implements the recursive version of the Quicksort algorithm.
// Have Quicksort return a pointer to an STL list.
// Use the two pointers to those list and splitting value to combine the result into a dynamically allocated STL list.
// Return a pointer to this list.

#include <iostream>
#include <list>

// Function to partition an STL list into two lists based on a splitting value
template <typename T>
void partition ( const T &splitting_value , std::list<T> &original_list , std::list<T> *less_list , std::list<T> *greater_list )
{
     for ( auto it = original_list.begin ( ); it != original_list.end ( );)
     {
          if ( *it < splitting_value )
          {
               less_list->push_back ( *it );
               it = original_list.erase ( it );
          } else
          {
               greater_list->push_back ( *it );
               it = original_list.erase ( it );
          }
     }
}

// Recursive function to perform quicksort on an STL list
template <typename T>
void quickSort ( std::list<T> &original_list )
{
     if ( original_list.size ( ) <= 1 )
          return;

     T splitting_value = original_list.back ( );
     original_list.pop_back ( );

     std::list<T> *less_list = new std::list<T>;
     std::list<T> *greater_list = new std::list<T>;

     partition ( splitting_value , original_list , less_list , greater_list );

     quickSort ( *less_list );      // Recursively sort the "less" list
     quickSort ( *greater_list );   // Recursively sort the "greater" list

     original_list.splice ( original_list.end ( ) , *less_list );
     original_list.push_back ( splitting_value );
     original_list.splice ( original_list.end ( ) , *greater_list );

     delete less_list;
     delete greater_list;
}

// Wrapper function to start quicksort and return a pointer to the sorted list
template <typename T>
std::list<T> *quicksort ( std::list<T> input_list )
{
     quickSort ( input_list );
     std::list<T> *sorted_list = new std::list<T> ( input_list );
     return sorted_list;
}

int main ( )
{
    // Create an example list of integers
     std::list<int> myList = { 3, 6, 8, 10, 1, 2, 1 };

     // Call the quicksort function to sort the list recursively
     std::list<int> *sortedList = quicksort ( myList );

     // Print the sorted list
     std::cout << "Sorted List: ";
     for ( const int &val : *sortedList )
     {
          std::cout << val << " ";
     }
     std::cout << std::endl;

     // Don't forget to delete the dynamically allocated list to prevent memory leaks
     delete sortedList;

     return 0;
}