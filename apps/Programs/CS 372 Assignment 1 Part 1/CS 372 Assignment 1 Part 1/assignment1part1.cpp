// Assignment 01 - Part 01 - Raw Pointers Can Be Quite Evil
// Due : Wed Aug 23,2023 11 : 59pm
//
// File:   assignment1part1.cpp
// Author: Kaylee Lewis
// 
// Purpose:
// Illustrate some of the bad things that can happen with pointers
//

#include <iostream>

using namespace std;

// First case function
void firstCaseFunction() 
{
  const int arraySize = 1000000;

  // Allocate memory for an array of integers on the heap
  int* firstPointer = new int[arraySize];
  int* secondPointer = firstPointer;

  // Initialize the array with values from 0 to arraySize - 1
  for (int i = 0; i < arraySize; ++i) 
  {
    firstPointer[i] = i;
  }

  // Delete the allocated memory
  delete[] firstPointer;

  // Attempt to access and print the first ten integers pointed to by
  // secondPointer
  for (int i = 0; i < 10; ++i) 
  {
    // Exception thrown 
    cout << secondPointer[i] << " ";
  }

  cout << endl;
}

// memory has been deallocated, trying to access it leads to undefined behavior

// Second case function
void secondCaseFunction() 
{
  const int arraySize = 1000000;

  // Allocate memory for an array of integers on the heap
  int* firstPointer = new int[arraySize];
  int* secondPointer = firstPointer;

  // Delete the allocated memory
  delete[] firstPointer;

  // Print the address of secondPointer
  cout << "Address of the second pointer: " << secondPointer << endl;

  // Attempt to access and print the first ten integers pointed to by
  // secondPointer
  for (int i = 0; i < 10; ++i) 
  {
    cout << secondPointer[i] << " ";
  }

  cout << endl;
}

// Exception is thrown causing the program to crash since the pointer is pointing
// to deallocated memory.

string* createString() 
{
  string* strPtr = new string("abcdefghijkl");
  return strPtr;
}

// Third case function
void stringfunction() 
{
  // Create a string pointer on the stack and initialize it with the value from
  // the heap
  string* heapStringPtr = createString();
  string stackString = *heapStringPtr;

  // Delete the heap-allocated string
  delete heapStringPtr;

  // Print the string copied to the stack
  cout << "Print the string from the heap: " << stackString << endl;
}

// Trying to access the deleted heap-allocated memory can cause issues 

int main() 
{
  cout << "The first case:" << endl;
  firstCaseFunction();

  cout << endl << "The second case:" << endl;
  secondCaseFunction();

  cout << endl << "The third case:" << endl;
  createString();

  return 0;
}

// Exception thrown at 0x00007FF7B787585F in CS 372 Assignment 1 Part 1.exe: 
// 0xC0000005: Access violation reading location 0x000001F33ADFD070.
//
// The program attempted to read from a memory location that it did not have
// access to.
//
// Need to delete dynamically allocated memory only when done using it and 
// dont try to access it after its been deleted.
//
// Smart pointers can help manage the memory better than raw pointers.
//
// Avoid mixing stack and heap memory.