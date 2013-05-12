#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "llist.h"

template <typename T>
class Stack: private LList<T> {
  public:
  	Stack();					// Default constructor that calls the default constructor of LList
  	~Stack();					// Default destructor that calls the default destructor of LList
  	int size() const;			// Returns the size of the Stack by calling 
  	void push(const T& value);	// Push a value to the top of the stack
  	void pop();					// Pop a value off the top of the stack
  	T& top();					// Return the value at the top of the stack
  	bool empty() const;			// Return true if stack is empty, false otherwise
};

template <typename T>
Stack<T>::Stack():LList<T>() { };

template <typename T>
Stack<T>::~Stack()
{
	LList<T>::~LList();
}

template <typename T>
int Stack<T>::size() const
{
	return LList<T>::size();
}

template <typename T>
void Stack<T>::push(const T& value)
{
	this->push_back(value);
}

template <typename T>
void Stack<T>::pop()
{
	this->pop_back();
}

template <typename T>
T& Stack<T>::top()
{
	try {
		return this->peek_back();
	} catch(std::invalid_argument a) {
		throw std::invalid_argument("stack.h:50: Stack empty");
	}
}

template <typename T>
bool Stack<T>::empty() const
{
	return LList<T>::empty();
}

#endif
