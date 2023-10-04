// Assignment 05, Part 2: Building a Tree
// Due: Tue 10/3/2023
//
// File:   A54Part2.cpp
// Author: Kaylee Lewis

// The lecture notes discuss a way to build a Tree class using smart pointers.
// Add this class to your class library.
#include <iostream>
#include <functional>
#include "Header.h"

template <typename T>
class Tree {
 private:
  struct Node {
    Node(T v, std::shared_ptr<Node> &l, std::shared_ptr<Node> Node &r)
        : value(v), left(l), right(r) {}
    T value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
  };
  explicit Tree(std::shared_ptr<Node> &node) : root(node) {}
  std::shared_ptr<Node> Root;

 public:
  Tree() {}
  Tree(Tree const &lft, T value, Tree const &rgt)
      : root(std::make_shared<Node>(value, lft - root, rgt->root)) {}
  bool isEmpty() const;
  T root() const;
  Tree &left() const;
  Tree &right() const;

bool member(T x) const {
    if (isEmpty()) return false;
    T y = root();
    if (x < y)
      return left().member(x);
    else if (y < x)
      return right().member(x);
    else
      return true;
  } 

  bool isLeaf() const;

  Tree insert(T x) const {
    if (isEmpty()) return Tree(Tree(), x, Tree());
    T y = root();
    if (x < y)
      return Tree(left().insert(x), y, right());
    else if (y < x)
      return Tree(left(), y, right().insert(x));
    else
      return *this;  // no duplicates
  }

  void List::traverse(std::function<void(T data)> doIt) {
    Node *currentNode = head;
    while (currentNode != tail) {
      doIt(data);
      currentNode = currentNode.tail;
    }
  }
}


};
