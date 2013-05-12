#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include "llist.h"

template <typename T>
class Queue: private LList<T> {
  public:
  	Queue();						// Default constructor that calls the default constructor of LList
  	~Queue();						// Default destructor that calls the default destructor of LList
  	int size() const;				// Return the size of the queue
  	void push_back(const T& value);	// Push a value to the back of the queue
  	void pop_front();				// Pop a value off the front of the queue
  	T& front();						// Return the value at the front of the queue
  	T& back();						// Return the value at the back of the queue
  	bool empty() const;				// Return true if queue is empty, false otherwise
};

template <typename T>
Queue<T>::Queue():LList<T>() { };

template <typename T>
Queue<T>::~Queue()
{
	LList<T>::~LList();
}

template <typename T>
int Queue<T>::size() const
{
	return LList<T>::size();
}

template <typename T>
void Queue<T>::push_back(const T& value)
{
	LList<T>::push_back(value);
}

template <typename T>
void Queue<T>::pop_front()
{
	LList<T>::pop_front();
}

template <typename T>
T& Queue<T>::front()
{
	try {
		return LList<T>::peek_front();
	} catch(std::invalid_argument a) {
		throw std::invalid_argument("queue.h:51: List empty");
	}
}

template <typename T>
T& Queue<T>::back()
{
	try {
		return this->peek_back();
	} catch(std::invalid_argument a) {
		throw std::invalid_argument("queue.h:61: Stack empty");
	}
}

template <typename T>
bool Queue<T>::empty() const
{
	return LList<T>::empty();
}

#endif
