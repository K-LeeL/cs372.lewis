// Assignment 02, Part 2: A Better Array
// Due : Tue Aug 29, 2023 11 : 59pm
//
// File:   assignment2part2.cpp
// Author: Kaylee Lewis
//
// Purpose:
//   Build an 'Array' template class for a class library based on the 'Vector'
//   cass from Part 1.
//

#include <iostream>

// Template parameter 'T', size_t parameter specifies size of array  
template <typename T, size_t Size>

class Array 
{
  private:

     T cArray[Size];
     size_t length = 0;

  public:
     // Constructor
     Array() : length(0) {}

    // Destructor
     ~Array() {}

     // Method to add new data to the array
     void push_back(T data) 
     {
          if (length < Size) 
          {
               cArray[length] = data;
               length++;
          } else 
          {
               std::cerr << "Array can not be added to. " << std::endl;
          }
     }
     
     // Access an element at a specific index
     T &at(size_t index) 
     {
          if (index >= length) 
          {
               std::cerr << "Array: index out of bounds on access" << std::endl;
               exit(1);
          } else 
          {
               return cArray[index];
          }
     }
    
     
     // Get the number of elements currently in the array
     size_t size() const
     {
          return length; 
     }

     // Get the maximum capacity of the array
     size_t capacity() const 
     { 
          return Size; 
     }

     // Indexing operator to access elements by index
     T &operator[](size_t index) 
     {  
          if (index >= length) 
          {
               std::cerr << "Array index out of bounds" << std::endl;
               exit(1);
          }

          return cArray[index]; 
     }

     // Print all elements in the array
     void traverse() 
     {
          for (size_t i = 0; i < length; ++i) 
          {
               std::cout << cArray[i] << " ";
          }

          std::cout << std::endl;
     }

    // Copy Constructor
     Array(const Array& other) : length(other.length) 
     {
          for (size_t i = 0; i < length; ++i) 
          {
               cArray[i] = other.cArray[i];
          }
     }

     // Copy Assignment Operator
     Array& operator=(const Array& other) 
     {
          if (this != &other) 
          {
               length = other.length;
               for (size_t i = 0; i < length; ++i) 
               {
                 cArray[i] = other.cArray[i];
               }
          }
          return *this;
     }

     // Method to return an iterator to the beginning of the array
     T* begin() 
     { 
          return cArray; 
     }

     // Method to return an iterator to the end of the array
     T* end() 
     { 
          return cArray + length; 
     }
};

int main() 
{

     Array<int, 10> a1;

     a1.push_back(5);
     a1.push_back(10);

     std::cout << "Array: ";

    for (auto& element : a1) 
    {
          std::cout  << element << " ";
    }
     std::cout << std::endl;

     return 0;
}