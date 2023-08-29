// Assignment 02, Part 1: Creating A Vector
// Due : Tue Aug 29, 2023 11 : 59pm
//
// File:   assignment2Part1.cpp
// Author: Kaylee Lewis
//
// Purpose:
//   Build a 'vector' class for a class library.
//

#include <vector>
#include <iostream>

// Template parameter 'T' allows vector of any data type
template <typename T>

class Vector
{
  private:
       T* Array = new T[1];
       int vCapacity = 1;
       int length = 0;

       // Method to expand the size of the vector
       void expand(int newCapacity) 
       {
          if (newCapacity > vCapacity) 
          {
               T* temp = new T[newCapacity];

               for (int i = 0; i < length; i++) 
               {
                    // Copy existing elements to the new array
                    temp[i] = Array[i];
               }

               delete[] Array;
               vCapacity = newCapacity;
               Array = temp;

          } else 
          {
               std::cerr << "vector::expand: new capacity is less than equal to current\n";
          }
       }

  public:
     // Constructor
     Vector() 
     {
          Array = new T[1];
          vCapacity = 1;
          length = 0;
     }


     // Destructor
     ~Vector() 
     {
          delete[] Array;
          Array = nullptr;
     }

     // Only special case where the index is equal to the capacity
     void put(T data, int index) 
     {
          if (index == vCapacity) 
          {
               // If index is at the end, use push_back
               push_back(data);

          } else 
          {
               // Update the element at the specified index
               Array[index] = data;

          }
     }

     // Method to add new data to the end of the vector
     void push_back(T data) 
     {
          // if number of elements is equal to capacity
          // than we need to reallocate and deep copy
          if (length == vCapacity) 
          {
               // Double the capacity if needed
               expand(2 * vCapacity);
          }

          Array[length] = data;
          length++;
     }

     // Access an element at a specific index
     T& at(int index) 
     {

          if (index < 0 || index >= length) 
          {
              std::cerr << "Vector: index out of bounds on access" << std::endl;
               exit(1);
          } else 
          {
               return Array[index];
          }
     }

     // Get the current number of elements in the vector
     int size() 
     { 
          return length; 
     }

     // Get the current capacity of the vector
     int capacity()
     {
          return vCapacity; 
     }

     // Print all elements in the vector
     void traverse()
     {
          for (int i = 0; i < length; i++)
          {
               std::cout << Array[i] << " ";
          }

          std::cout << std::endl;
     }

     // Compare two vectors for equality
     bool operator==(Vector& other) const 
     {
          if (other.size() != length) 
          {
               return false;
          } 
          else 
          {
          
               for (int i = 0; i < length; i++) 
               {
                    if (Array[i] != other.at(i)) 
                    {
                         return false;
                    }
               }
          }
          return true;
     };

     // Indexing operator to access elements by index
     T& operator[](int i) 
     {
          if ((i < 0) || (i >= length)) 
          {
               std::cerr << std::endl << "Vector index out of bounds" << std::endl;
               exit(1);
          }

          return Array[i];
     }

     // Copy constructor to work in concert with new operator
     Vector(const Vector& obj) 
     {

          // Reset self
          this->Array = new T[obj.capacity()];

          for (int i = 0; i < obj.size(); i++) 
          {
               Array[i] = obj.at(i);
          }
     }

     // Copy assignment operator
     Vector& operator=(const Vector& source) 
     {
          // Do a self check.
          if (this == &source) 
          {
               return *this;
          }

          // Clean up
          delete[] Array;
          Array = new T[1];
          vCapacity = 1;
          length = 1;

          for (int i = 0; i < source.size(); i++) 
          {
               push_back(source.at(i));
          }

          return *this;
     }

     // Method to return an iterator to the beginning of the vector
     T* begin() 
     { 
          return Array; 
     }

     // Method to return an iterator to the end of the vector
     T* end() 
     { 
          return Array + length; 
     }

};

int main() 
{
     Vector<int> v1, v2, v3;

     v1.push_back(10);
     v1.push_back(20);

     std::cout << "v1 = ";

     for (auto& v : v1) 
     {
          std::cout << v << " ";
     }

     std::cout << v1[0] << " " << v1[1] << std::endl;
     std::cout << std::endl;

     return 0;
}