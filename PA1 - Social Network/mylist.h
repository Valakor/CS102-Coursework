#ifndef MYLIST_H
#define MYLIST_H

#include <stdexcept>
#include <iostream>
using namespace std;

const int DEFAULT_LIST_SIZE = 10; // Default capacity for a MyList object with no 'capacity_' parameter given

template <typename T> class MyList {
public:
	MyList();				// Default constructor that instantiates a new array with size 0 and 'capacity_' equal to 'DEFAULT_LIST_SIZE'
	MyList(int capacity);	// Constructor that instantiates a new array with size 0 and 'capacity_' equal to 'capacity', which is given
	~MyList();				// Destructor that deletes 'data_'
	void push_back(T item);	// Adds 'item' to the end of 'data_' and adds 1 to 'size_'. If this operations exceeds current 'capacity_', a new array is created of 'capacity_' * 2 and all values are copied over to the new array
	bool remove(T item);	// Removes the first instance of 'item' in 'data_' and returns true. If 'item' does not exist, returns false
	T pop(int loc);			// Removes and returns the item at 'loc', shifts all further items down, and subtracts 1 from 'size_'
	T& at(int loc) const;	// Returns the item at 'loc'
	int size() const;		// Returns 'size_' of 'data_'
	T& operator[](int loc);	// Returns the item at 'loc' when using operator[]
private:
	T *data_;				// Dynamically created array of pointers to objects of type 'T'
	int size_;				// Current size of 'data_'
	int capacity_;			// Maximum 'size_' of data that determines the memory allocated for 'data_'. Increased automatically when needed
};


template<typename T> MyList<T>::MyList() {
	size_ = 0;
	capacity_ = DEFAULT_LIST_SIZE;
	data_ = new T[capacity_];
}

template<typename T> MyList<T>::MyList(int capacity) {
	size_ = 0;
	capacity_ = capacity;
	data_ = new T[capacity_];
}

template<typename T> MyList<T>::~MyList() {
	delete [] data_;
}

template<typename T> void MyList<T>::push_back(T item) {
	if (size_ >= capacity_) {
		T *tempArray_ = new T[capacity_*2];
		for (int i = 0; i < size_; i++) tempArray_[i] = data_[i];
		delete [] data_;
		data_ = tempArray_;
	}
	
	data_[size_++] = item;
}

template<typename T> bool MyList<T>::remove(T item) {
	for (int i = 0; i < size_; i++) {
		if (data_[i] == item) {
			for (int j = i + 1; j < size_; j++) {
				data_[j - 1] = data_[j];
			}
			size_--;
			return true;
		}
	}
	return false;
}

template<typename T> T MyList<T>::pop(int loc) {
	if (loc < 0 || loc >= size_) throw invalid_argument("Index out of bounds at call to \'pop\'.");
	
	T temp = data_[loc];
	for (int i = loc + 1; i < size_; i++) {
		data_[i - 1] = data_[i];
	}
	size_--;
	
	return temp;
}

template<typename T> T& MyList<T>::at(int loc) const {
	if (loc < 0 || loc >= size_) throw invalid_argument("Index out of bounds at call to \'at\'.");
	return data_[loc];
}

template<typename T> int MyList<T>::size() const {
	return size_;
}

template<typename T> T& MyList<T>::operator[](int loc) {
	if (loc < 0 || loc >= size_) throw invalid_argument("Index out of bounds using operator[].");
	return data_[loc];
}

#endif
