// Assignment 03, Part 3: Circular Lists
// Due: Tue Sep 5, 2023 11:59pm
//
// File:   assignment3part3.cpp
// Author: Kaylee Lewis
//
// Purpose:
//   Define a new class named CircularList that inherits from your List class
//   that changes the behavior of a list so that the tail of the list points at
//   the head and the head points at the tail.   You will need to keep track of
//   the head and tail correctly using separate variables.
//   Adjust the list methods so that they correctly deal with this new behavior
//   and add a method called circle that, given a starting position in the list,
//   traverses the entire list, starting and ending at the given starting point.
//
// https://www.geeksforgeeks.org/circular-singly-linked-list-insertion/
// https://www.geeksforgeeks.org/traversal-of-circular-linked-list/
// https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.linkedlist-1?view=net-7.0#constructors

#include <iostream>
#include "Library.h"

template< typename T >
// Define a new class that inherits from the list class
class CircularList : public List<T> {
 public:
  // Constructor
  CircularList() : List<T>() {
    // Making the list circular
    this->tail->next = this->head->next;
    this->head->next->prev = this->tail;
  }

  // Overriding push_front to maintain the circular nature
  void push_front(T data) {
    List<T>::push_front(data);  // Call the base class push_front
    // Additional step to maintain the circular nature
    this->tail->next = this->head->next;
    this->head->next->prev = this->tail;
  }

  // Method to traverse the list from a given starting point
  void circle(int startPos) {
    if (startPos >= this->length || startPos < 0) {
      throw std::out_of_range("Invalid starting position");
    }

    typename List<T>::Node *current = this->head->next;
    for (int i = 0; i < startPos; ++i) {
      current = current->next;
    }

    typename List<T>::Node *startNode = current;

    do {
      std::cout << current->data << " ";
      current = current->next;
    } while (current != startNode && current != this->tail);

    std::cout << std::endl;
  }
};

int main( )
{
  // Create a Circular List instance
  CircularList< int > cList;

  // Add elements to the circular list
  cList.push_back( 1 );
  cList.push_back(2);
  cList.push_back(4);
  cList.push_back(5);

  // Perform circular traversal starting from position 2
  for (int &value : cList) {
    std::cout << value << " ";
  }
  std::cout << std::endl;


  return 0;
}
