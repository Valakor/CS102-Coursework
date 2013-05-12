#ifndef USER_H
#define USER_H
#include "mylist.h"

class User {
public:
	User();											// Default constructor that sets all User info to initial values
	User(int id, string name, int age, int zip);	// Constructor that creates a User with given 'id', 'name', 'age', and 'zip'
	int getId() const;								// Returns the 'id_' of the current user
	string getName() const;							// Returns the 'name_' of the current user
	int getAge() const;								// Returns the 'age_' of the current user
	int getZip() const;								// Returns the 'zip_' of the current user
	void addFriend(int id);							// Adds 'id' to current user's 'friendList_' if it does not already exist
	void removeFriend(int id);						// Removes 'id' from current user's 'friendList_' if it exists
	int getFriends() const;							// Returns the number of friends User has
	int getFriendId(int loc) const;					// Returns the id of the friend at 'loc' in User's 'friendList_'
private:
	string name_;				// User's name	
	int id_;					// User's id
	int age_;					// User's age
	int zip_;					// User's zip code
	MyList<int> friendList_;	// User's list of friends according to their 'id_'
};

#endif
