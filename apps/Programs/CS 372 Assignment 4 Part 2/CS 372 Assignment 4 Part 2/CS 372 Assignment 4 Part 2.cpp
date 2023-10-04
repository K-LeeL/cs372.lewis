// Assignment 04, Part 2: Adding iterators to other classes
// Due: Tue Sep 12, 2023 11:59pm
//
// File:   assignment4part2.cpp
// Author: Kaylee Lewis

// Purpose: In lecture, we built a base class for sequential containers  and
// modified the list, stack, and queue data structures to inherit  from that
// `SequentialContainer` class. Modify your `Vector` and  `Array` classes to be
// derived classes of `SequentialContainer`,    noting that for both classes you
// will be able to build the iterator using the vector or array indexes.
//

#include <iostream>

//Define SequentialContainer Class

template <typename T>
class SeqContainer {
 protected:
  class Node {
   public:
    T data;
    Node *prev;
    Node *next;
    bool isHiddenNode = false;
    Node() = default;
    Node(T d, Node *p, Node *n) : data(d), prev(p), next(n){};
  };
  Node *head;
  Node *tail;

  void setupList() {
    Node *newNode = new Node();
    newNode->next = tail;
    newNode->prev = head;
    head->next = newNode;
    tail->prev = newNode;
  }
  void deleteListContents() {
    Node *current = head->next;
    Node *temp = nullptr;
    while (current != tail->prev) {
      temp = current->next;
      delete current;
      current = temp;
    }
  }

 public:
  class const_iterator {
   protected:
    Node *current;
    T &retrieve() const { return current->data; }
    const_iterator(Node *p) : current(p) {}
    friend class SeqContainer<T>;

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
  };

 public:
  class iterator : public const_iterator {
   protected:
    iterator(Node *p) : const_iterator(p) {}
    friend class SeqContainer<T>;

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
  };

  SeqContainer() {
    head = new Node();
    head->isHiddenNode = true;
    tail = new Node();
    tail->isHiddenNode = true;
    head->prev = nullptr;
    head->next = tail;
    tail->prev = head;
    tail->next = nullptr;
  }

  SeqContainer(T newData) {
    setupList();
    (head->next)->data = newData;
  }

  SeqContainer(SeqContainer &rhs) {
    // copy constructor
    deleteListContents();
    head = rhs.head;
    tail = rhs.tail;
  }

  virtual ~SeqContainer() {
    // And a destructor
    deleteListContents();
    delete head;
    delete tail;
  }
  // iterator related methods
  virtual iterator begin() { return {head->next}; }

  virtual iterator end() { return tail; }

  virtual const_iterator cbegin() const { return {head->next}; }

  virtual const_iterator cend() const { return {tail}; }

  virtual iterator insert(iterator itr, const T &x) {
    Node *p = itr.current;
    Node *newNode = new Node{x, p->prev, p};
    p->prev = p->prev->next = newNode;
    return itr;
  }

  virtual iterator erase(iterator itr) {
    Node *p = itr.current;
    iterator iterToReturn{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    return iterToReturn;
  }

  virtual iterator erase(iterator from, iterator to) {
    iterator itr = from;
    while (itr != to) {
      itr = erase(itr);
    }
    return to;
  }
};


int main() {

}
