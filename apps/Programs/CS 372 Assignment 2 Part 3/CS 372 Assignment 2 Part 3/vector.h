// vector.h

// File:   assignment2part1.cpp
// Author: Kaylee Lewis

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

class VecTester {
 private:
  Vector<int> testVector = Vector<int>();

  void fillVector(size_t cap) {
    for (int i = 0; i < cap; ++i) {
      testVector[i] = i;
    }
  }

 public:
  void tester() {
    size_t currentCap = testVector.capacity();
    std::cout << "Starting capacity: " << currentCap << std::endl;
    for (int i = 0; i <= 500; i++) {
      if ((i % PrintInterval) == 0) {
        std::cout << "Current cap: " << currentCap << std::endl;
      }
      auto start = std::chrono::steady_clock::now();
      testVector.push_back(i);
      auto end = std::chrono::steady_clock::now();
      currentCap = testVector.capacity();
      std::chrono::duration<double> elaspedSeconds = end - start;
      if ((i % PrintInterval) == 0) {
        std::cout << "For increase capacity to " << currentCap << " took "
                  << elaspedSeconds.count() << " seconds" << std::endl;
      }
    }
  }
};