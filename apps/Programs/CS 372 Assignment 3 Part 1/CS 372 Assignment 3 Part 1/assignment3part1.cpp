// Assignment 03, Part 1 - Make A List
// Due: Tue Sep 5, 2023 11:59pm
//
// File:   assignment3part1.cpp
// Author: Kaylee Lewis
//
// Purpose:
//   Add the `ist class to the library, with any required test code to verify
//   they are operating correctly.
//
#pragma once

#include <iostream>

#include "Library.h"

template <typename T>

class List {
 private:
  // Node for a linked list.
  struct Node {
   public:
    T data;
    Node *next;
    Node *prev;
    bool isHiddenNode = false;
  };

  Node *head;
  Node *tail;
  int length;

 public:
  // Add const_iterator for test
  class const_iterator {
   public:
    const_iterator() : current(nullptr) {}

    T &operator*() const { return retrieve(); }

    const_iterator &operator++() {
      current = current->next;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator old = *this;
      ++(*this);
      return old;
    }

    bool operator==(const const_iterator &rhs) const {
      return current == rhs.current;
    }

    bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }

   protected:
    Node *current;

    T &retrieve() const { return current->data; }

    const_iterator(Node *p) : current(p) {}

    friend class List<T>;
  };

  // Iterator added for test
  class iterator : public const_iterator {
   public:
    iterator() {}

    T &operator*() { return const_iterator::retrieve(); }

    const T &operator*() const { return const_iterator::operator*(); }

    iterator &operator++() {
      this->current = const_iterator::current->next;
      return *this;
    }

    iterator operator++(int) {
      iterator old = *this;
      ++(*this);
      return old;
    }

   protected:
    iterator(Node *p) : const_iterator(p) {}

    friend class List<T>;
  };

 private:
  void setupList() {
    Node *newNode = new Node();
    newNode->next = tail;
    newNode->prev = head;
    head->next = newNode;
    tail->prev = newNode;
  }

  void deleteListContents() {
    Node *current = head->next;
    while (current != tail) {
      Node *temp = current;
      current = current->next;
      delete temp;
    }
    head->next = tail;
    tail->prev = head;
  }

 public:
  // Constructor: initialize an empty list.
  List() {
    head = new Node();
    head->isHiddenNode = true;
    tail = new Node();
    tail->isHiddenNode = true;
    head->prev = nullptr;
    head->next = tail;
    tail->prev = head;
    tail->next = nullptr;
    length = 0;
  }

  List(T newData) {
    setupList();
    (head->next)->data = newData;
  }

  List(List &rhs) {
    // copy constructor
    deleteListContents();
    head = rhs.head;
    tail = rhs.tail;
  }

  // Destructor: clear the list.
  ~List() {
    deleteListContents();
    delete head;
    delete tail;
  }

  // Assignment Operator
  List &operator=(const List<T> &other) {
    if (this == &other) {
      return *this;
    }
    clear();
    Node *current = other.head->next;
    while (current != other.tail) {
      push_back(current->data);
      current = current->next;
    }
    return *this;
  }

  // Check if the list is empty
  bool empty() const { return (head->next == tail); }

  // begin and end added for test
  iterator begin() { return iterator{head->next}; }

  iterator end() { return iterator{tail}; }

  const_iterator cbegin() const { return const_iterator{head->next}; }

  const_iterator cend() const { return const_iterator{tail}; }

  iterator erase(iterator itr) {
    Node *p = itr.current;
    iterator iterToReturn{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    return iterToReturn;
  }

  iterator insert(iterator itr, const T &x) {
    Node *p = itr.current;
    Node *newNode = new Node{x, p->prev, p};
    p->prev->next = newNode;
    p->prev = newNode;
    length++;
    return iterator{newNode};
  }

  iterator erase(iterator from, iterator to) {
    iterator itr = from;
    while (itr != to) {
      itr = erase(itr);
    }
    return to;
  }

  // Add an element to the front of the list
  void push_front(T data) {
    if (this->empty()) {
      setupList();
      Node *actualHead = head->next;
      actualHead->data = data;
    } else {
      Node *actualHead = head->next;
      Node *newNode = new Node();
      newNode->data = data;
      newNode->next = actualHead;
      actualHead->prev = newNode;
      newNode->prev = head;
      head->next = newNode;
    }
  }

  // Add an element to the back of the list
  void push_back(T data) {
    if (this->empty()) {
      setupList();
      Node *actualTail = tail->prev;
      actualTail->data = data;
    } else {
      Node *actualTail = tail->prev;
      Node *newNode = new Node();
      newNode->data = data;
      newNode->prev = actualTail;
      actualTail->next = newNode;
      newNode->next = tail;
      tail->prev = newNode;
    }
  }

  // Get the first element in the list (front)
  T front() {
    Node *actualHead = head->next;
    return (actualHead->data);
  }

  // Get the last element in the list (back)
  T back() {
    Node *actualTail = tail->prev;
    return (actualTail->data);
  }

  // Remove the last element from the list
  void pop_back() {
    if (!empty()) {
      Node *lastNode = tail->prev;
      tail->prev = lastNode->prev;
      Node *newLastNode = tail->prev;
      newLastNode->next = tail;
      delete lastNode;
      lastNode = nullptr;
      length--;
    } else {
      std::cerr << "pop_back(): Attempt to pop from empty list. " << std::endl;
    }
  }

  // Remove the first element from the list
  void pop_front() {
    if (!empty()) {
      Node *firstNode = head->next;
      head->next = firstNode->next;
      Node *newFirstNode = head->next;
      newFirstNode->prev = head;
      delete firstNode;
      firstNode = nullptr;
      length--;
    } else {
      std::cerr << "pop_back(): Attempt to pop from empty list. " << std::endl;
    }
  }

  // Traverse the list and apply a function to each element
  void traverse(void (*doIt)(T &)) {
    Node *current = head->next;
    while (current != tail) {
      doIt(current->data);
      current = current->next;
    }
  }

  // Clear the list
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  // Compare two lists
  bool operator==(const List &other) const {
    if (length != other.length) {
      return false;
    }
    Node *current = head->next;
    Node *otherCurrent = other.head->next;
    while (current != tail && otherCurrent != other.tail) {
      if (current->data != otherCurrent->data) {
        return false;
      }
      current = current->next;
      otherCurrent = otherCurrent->next;
    }
    return true;
  }

  // Get the number of elements in the list
  int size() const { return length; }
};


// Function for test
void printItem( int &item )
{
    std::cout << item << " ";
}

int main( )
{
    // Create a list
    List< int > myList;

    // Add some elements to the list
    myList.push_back( 1 );
    myList.push_back( 2 );
    myList.push_back( 3 );

    // Print the elements in the list
    std::cout << "The content of the list is:" << std::endl;
    myList.traverse( printItem );
    std::cout << std::endl;

    // Access elements by index
    std::cout << "The front element is: " << myList.front( ) << std::endl;

    // Remove the front element
    myList.pop_front( );

    // Check the size of the list
    std::cout << "The size of the list after pop is: " << myList.size( ) << std::endl;

    // Create another list and copy the contents
    List< int > anotherList;
    anotherList = myList;

    // Check if the two lists are equal
    if( myList == anotherList )
    {
        std::cout << "The lists are equal." << std::endl;
    } else
    {
        std::cout << "The lists are not equal." << std::endl;
    }

    // Clear the original list
    myList.clear( );

    // Check the size of the cleared list
    std::cout << "The cleared list size is: " << myList.size( ) << std::endl;

    //Test
    List< int > aListOfIntegers;
    if( aListOfIntegers.empty( ) )
    {
        std::cout << "Yep, the new list is empty. " << std::endl;
    }
    for( int i = 3 ; i >= 0 ; i-- )
    {
        aListOfIntegers.push_front( i );
    }
    aListOfIntegers.traverse( printItem );
    std::cout << std::endl;

    std::cout << "Test iterators: Mutable -> ";
    for( auto iter = aListOfIntegers.begin( ) ; iter != aListOfIntegers.end( ) ; ++iter )
    {
        std::cout << *iter << " ";
    }

    std::cout << "Test iterators: const -> ";
    for( auto iter = aListOfIntegers.cbegin( ) ; iter != aListOfIntegers.cend( ) ; ++iter )
    {
        std::cout << *iter << " ";
    }

    std::cout << std::endl;
    for( int i = 0 ; i < 3 ; i++ )
    {
        int datum = aListOfIntegers.back( );
        std::cout << datum << " ";
        aListOfIntegers.pop_back( );
    }
    std::cout << std::endl;
    if( !aListOfIntegers.empty( ) )
    {
        aListOfIntegers.traverse( printItem );
        std::cout << std::endl;
    }
    aListOfIntegers.push_back( 42 );
    aListOfIntegers.traverse( printItem );
    std::cout << std::endl;
}
