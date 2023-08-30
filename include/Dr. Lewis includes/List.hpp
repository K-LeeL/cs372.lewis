
#pragma once
#include <functional>
#include "SeqContainer.hpp"

template <typename T>
class List : public SeqContainer<T> {
public:
	List() {};
	List(T newData) : SeqContainer<T>(newData) {}
	List(List &rhs) : SeqContainer<T>(rhs) {	}

	~List(){ }
  
	bool empty() {
		return ( head->next == tail );
	}

	// And the methods for the rest 
	void push_front(T data) {
		if (this->empty()){
			setupList();
			Node * actualHead = head->next;
			actualHead->data = data;
		}
		else {
			Node *actualHead = head->next;
			Node *newNode = new Node();
			newNode->data = data;
			newNode->next = actualHead;
			actualHead->prev = newNode;
			newNode->prev = head;
			head->next = newNode;
		}
	}
	void push_back(T data) {
		if (this->empty()) {
			setupList();
			Node *actualTail = tail->prev;
			actualTail->data = data;
		}
		else {
			Node *actualTail = tail->prev;
			Node *newNode = new Node();
			newNode->data = data;
			newNode->prev = actualTail;
			actualTail->next = newNode;
			newNode->next = tail;
			tail->prev = newNode;
		}
	}
	T front() {
		Node *actualHead = head->next;
		return (actualHead->data);
	}
	T back() {
		Node *actualTail = tail->prev;
		return (actualTail->data);
	}
	void pop_back() {
		if (!empty()) {
			Node *lastNode = tail->prev;
			tail->prev = lastNode->prev;
			Node *newLastNode = tail->prev;
			newLastNode->next = tail;
			delete lastNode;
			lastNode = nullptr;
		}
		else {
			std::cerr << "pop_back(): Attempt to pop from empty list. " << std::endl;
		}
	}
	void pop_front() {
		if (!empty()) {
			Node *firstNode = head->next;
			head->next = firstNode->next;
			Node *newFirstNode = head->next;
			newFirstNode->prev = head;
			delete firstNode;
			firstNode = nullptr;
		}
		else {
			std::cerr << "pop_back(): Attempt to pop from empty list. " << std::endl;
		}
	}
	void traverse(std::function<void(T &data)> doIt) {
		Node *current = head->next;
		while (current != tail) {
			doIt(current->data);
			current = current->next;
		}
	}
};
