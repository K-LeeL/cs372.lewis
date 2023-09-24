//Header.h
#pragma once
#include <iostream>

template <typename T>
class List {
 public:
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

  List(const List &rhs) {
    head = new Node();
    tail = new Node();
    setupList();
    Node *current = rhs.head->next;
    while (current != rhs.tail) {
      push_back(current->data);
      current = current->next;
    }
  }

  // Destructor: clear the list.
  ~List() {
    deleteListContents();
    delete head;
    delete tail;
    head = nullptr;
    tail = nullptr;
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
      std::cerr << "pop_front(): Attempt to pop from empty list. " << std::endl;
    }
  }

  void traverse(void (*doIt)(T &data)) {
    Node* current = head;
    while (current != nullptr) {
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

  // Get the number of elements in the list
  int size() const { return length; }
};

template <typename T>
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
