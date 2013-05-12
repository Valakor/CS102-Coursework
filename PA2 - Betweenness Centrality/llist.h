#ifndef LLIST_H
#define LLIST_H

#include <stdexcept>

template <typename T>
struct Item {
  T val;
  Item<T> *next;
};

template <typename T>
class LList {
  public:
	LList();
	~LList();
	bool empty() const;
	int size() const;
	void clear();
	void push_back(const T& new_val);
	void pop_front();
	void pop_back();
	T& peek_front() const;
	T& peek_back() const;
	T& at(int loc) const;
	T& operator[](int loc);

  private:
	Item<T> *head_;
	Item<T> *tail_;
	int size_;
};

// Write the constructor here
template <typename T>
LList<T>::LList(): head_(NULL), tail_(NULL), size_(0) {};

// Write the destructor here
template <typename T>
LList<T>::~LList()
{
	clear();
}

// Returns whether list is empty or not
template <typename T>
bool LList<T>::empty() const
{
	return head_ == NULL;
}

// Returns size_ of llist
template <typename T>
int LList<T>::size() const
{
	return size_;
}

// Adds new_val to ends of llist
template <typename T>
void LList<T>::push_back(const T& new_val)
{
	Item<T>* newItem = new Item<T>;
	newItem->val = new_val;
	newItem->next = NULL;
	if (size_ == 0) tail_ = newItem;
	else {
		tail_->next = newItem;
		tail_ = newItem;
	}
	if (size_ == 0) head_ = newItem;
	size_++;
} 

// Removes item at front of llist
template <typename T>
void LList<T>::pop_front()
{
	if (size_ <= 0) return;
	if (size_ == 1) {
		delete head_;
		head_ = NULL;
		tail_ = NULL;
	} else {
		Item<T>* temp = head_->next;
		delete head_;
		head_ = temp;
	}
	size_--;
}

// Removes item at back of list
template <typename T>
void LList<T>::pop_back()
{
	if (size_ <= 0) return;
	Item<T>* temp = head_;
	
	if (size_ == 1) {
		delete head_;
		head_ = NULL;
		tail_ = NULL;
	} else {
		for (int i = 0; i < size_ - 2; i++) {
			temp = temp->next;
		}
		temp->next = NULL;
		delete tail_;
		tail_ = temp;
	}
	
	size_--;
}

// 
template <typename T>
T& LList<T>::peek_front() const
{
	if (size_ <= 0) throw std::invalid_argument("llist.h:119: No items in list");
	return head_->val;
}

//
template <typename T> 
T& LList<T>::peek_back() const
{
	if (size_ <= 0) throw std::invalid_argument("llist.h:127: No items in list");
	return tail_->val;
}

// Returns the val of the item at loc
template <typename T>
T& LList<T>::at(int loc) const
{
	if (loc < 0 || loc >= size_) throw std::invalid_argument("llist.h:135: Index out of bounds");
	Item<T>* temp = head_;
	for (int i = 0; i < loc; i++) {
		temp = temp->next;
	}
	return temp->val;
}

// Clears entire list
template <typename T>
void LList<T>::clear()
{
	while(head_ != NULL){
 		Item<T> *temp = head_->next;
    	delete head_;
    	head_ = temp;
  	}
}

// Operator overload for []
template <typename T>
T& LList<T>::operator[](int loc)
{
	if (loc < 0 || loc >= size_) throw std::invalid_argument("llist.h:158: Index out of bounds");
	Item<T>* temp = head_;
	for (int i = 0; i < loc; i++) {
		temp = temp->next;
	}
	return temp->val;
}

#endif
