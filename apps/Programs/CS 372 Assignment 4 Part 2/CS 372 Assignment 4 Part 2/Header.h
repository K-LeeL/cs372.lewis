#pragma once

#include <chrono>
#include <iostream>

const int PrintInterval = 10;

// Template parameter 'T' allows vector of any data type
template <typename T>

class Vector {
 private:
  T* vArray = new T[1];
  int vCapacity = 1;
  int length = 0;

  // Method to expand the size of the vector
  void expand(int newCapacity) {
    if (newCapacity > vCapacity) {
      T* temp = new T[newCapacity];

      for (int i = 0; i < length; i++) {
        // Copy existing elements to the new array
        temp[i] = vArray[i];
      }

      delete[] vArray;
      vCapacity = newCapacity;
      vArray = temp;

    } else {
      std::cerr
          << "vector::expand: new capacity is less than equal to current\n";
    }
  }

 public:
  // Constructor
  Vector() {
    vArray = new T[1];
    vCapacity = 1;
    length = 0;
  }

  // Destructor
  ~Vector() {
    delete[] vArray;
    vArray = nullptr;
  }

  // Only special case where the index is equal to the capacity
  void put(T data, int index) {
    if (index == vCapacity) {
      // If index is at the end, use push_back
      push_back(data);

    } else {
      // Update the element at the specified index
      vArray[index] = data;
    }
  }

  // Method to add new data to the end of the vector
  void push_back(T data) {
    // if number of elements is equal to capacity
    // than we need to reallocate and deep copy
    if (length == vCapacity) {
      // Double the capacity if needed
      expand(2 * vCapacity);
    }

    vArray[length] = data;
    length++;
  }

  // Access an element at a specific index
  T& at(int index) {
    if (index < 0 || index >= length) {
      std::cerr << "Vector: index out of bounds on access" << std::endl;
      exit(1);
    } else {
      return vArray[index];
    }
  }

  // Get the current number of elements in the vector
  int size() { return length; }

  // Get the current capacity of the vector
  int capacity() { return vCapacity; }

  // Print all elements in the vector
  void traverse() {
    for (int i = 0; i < length; i++) {
      std::cout << vArray[i] << " ";
    }

    std::cout << std::endl;
  }

  // Compare two vectors for equality
  bool operator==(Vector& other) const {
    if (other.size() != length) {
      return false;
    } else {
      for (int i = 0; i < length; i++) {
        if (vArray[i] != other.at(i)) {
          return false;
        }
      }
    }
    return true;
  };

  // Indexing operator to access elements by index
  T& operator[](int i) {
    if ((i < 0) || (i >= length)) {
      std::cerr << std::endl << "Vector index out of bounds" << std::endl;
      exit(1);
    }

    return vArray[i];
  }

  // Copy constructor to work in concert with new operator
  Vector(const Vector& obj) {
    // Reset self
    this->vArray = new T[obj.capacity()];

    for (int i = 0; i < obj.size(); i++) {
      vArray[i] = obj.at(i);
    }
  }

  // Copy assignment operator
  Vector& operator=(const Vector& source) {
    // Do a self check.
    if (this == &source) {
      return *this;
    }

    // Clean up
    delete[] vArray;
    vArray = new T[1];
    vCapacity = 1;
    length = 1;

    for (int i = 0; i < source.size(); i++) {
      push_back(source.at(i));
    }

    return *this;
  }

  // Method to return an iterator to the beginning of the vector
  T* begin() { return vArray; }

  // Method to return an iterator to the end of the vector
  T* end() { return vArray + length; }
};

// Template parameter 'T', size_t parameter specifies size of array
template <typename T, size_t Size>

class Array {
 private:
  T cArray[Size];
  size_t length = 0;

 public:
  // Constructor
  Array() : length(0) {}

  // Destructor
  ~Array() {}

  // Method to add new data to the array
  void push_back(T data) {
    if (length < Size) {
      cArray[length] = data;
      length++;
    } else {
      std::cerr << "Array can not be added to. " << std::endl;
    }
  }

  // Access an element at a specific index
  T& at(size_t index) {
    if (index >= length) {
      std::cerr << "Array: index out of bounds on access" << std::endl;
      exit(1);
    } else {
      return cArray[index];
    }
  }

  // Get the number of elements currently in the array
  size_t size() const { return length; }

  // Get the maximum capacity of the array
  size_t capacity() const { return Size; }

  // Indexing operator to access elements by index
  T& operator[](size_t index) {
    if (index >= length) {
      std::cerr << "Array index out of bounds" << std::endl;
      exit(1);
    }

    return cArray[index];
  }

  // Print all elements in the array
  void traverse() {
    for (size_t i = 0; i < length; ++i) {
      std::cout << cArray[i] << " ";
    }

    std::cout << std::endl;
  }

  // Copy Constructor
  Array(const Array& other) : length(other.length) {
    for (size_t i = 0; i < length; ++i) {
      cArray[i] = other.cArray[i];
    }
  }

  // Copy Assignment Operator
  Array& operator=(const Array& other) {
    if (this != &other) {
      length = other.length;
      for (size_t i = 0; i < length; ++i) {
        cArray[i] = other.cArray[i];
      }
    }
    return *this;
  }

  // Method to return an iterator to the beginning of the array
  T* begin() { return cArray; }

  // Method to return an iterator to the end of the array
  T* end() { return cArray + length; }
};
