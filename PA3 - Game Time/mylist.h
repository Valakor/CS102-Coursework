#ifndef MYLIST_H
#define MYLIST_H

#include <stdexcept>
#include <iostream>

const int DEFAULT_LIST_SIZE = 10;

/** A dynamic, unbounded, templated array-based List class. 
 * @author Matthew Pohlmann
 */

template <typename T> class MyList {
public:
	/** Default constructor. Instantiates a new array with size 0
	 * and capacity equal to 10. */
	MyList();
	
	/** Overloaded constructor. Instantiates a new array with size 0
	 * and capacity equal to a given capacity.
	 * @param capacity The initial capacity of the List */ 
	MyList(int capacity);
	
	/** Default destructor. Deletes all internal data that was created
	 * dynamically. */
	~MyList();
	
	/** Adds an item to the end of the list. If this operations exceeds
	 * the list's current capacity, a new array is created of size (capacity * 2)
	 * and all values are copied over to the new array.
	 * @post The list's size is incremented by 1
	 * @param item The templated item to be added to the list */
	void push_back(T item);
	
	/** Removes the first instance of item in the list.
	 * @post The list's size is decremented by 1.
	 * @param item The templated item to be removed from the list
	 * @return True if the item is successfully removed, false if it did not exist in the list */
	bool remove(T item);
	
	/** Removes and returns the item at loc.
	 * @post All further items in the list are shifted down
	 * @post The list's size is decremented by 1
	 * @param loc The location of the item to be removed
	 * @return The templated item that is removed */
	T pop(int loc);
	
	/** Returns the item at loc.
	 * @param loc The location of the item to be returned.
	 * @return A reference to a templated item of type T */
	T& at(int loc) const;
	
	/** Returns the size of the list.
	 * @return An int corresponding to the number of items in the list */
	int size() const;
	
	/** Overloaded [ ] operator. Returns the item at loc.
	 * @param loc The location of the item to be returned.
	 * @return A reference to a templated item of type T */
	T& operator[](int loc);
	
private:
	/** Dynamically created array of pointers to objects of type T */
	T *data_;
	/** Current size of data_ */
	int size_;
	/** Maximum size_ of data_ that determines the memory allocated for data_. Increases dynamically when needed */
	int capacity_;
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
		capacity_ *= 2;
		T *tempArray_ = new T[capacity_];
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
	if (loc < 0 || loc >= size_) throw std::invalid_argument("mylist.h:114: index out of bounds");
	
	T temp = data_[loc];
	for (int i = loc + 1; i < size_; i++) {
		data_[i - 1] = data_[i];
	}
	size_--;
	
	return temp;
}

template<typename T> T& MyList<T>::at(int loc) const {
	if (loc < 0 || loc >= size_) throw std::invalid_argument("mylist.h:126: index out of bounds");
	return data_[loc];
}

template<typename T> int MyList<T>::size() const {
	return size_;
}

template<typename T> T& MyList<T>::operator[](int loc) {
	if (loc < 0 || loc >= size_) throw std::invalid_argument("mylist.h:135: index out of bounds");
	return data_[loc];
}

#endif
