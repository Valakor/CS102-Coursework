# Design Document for PA1

## Purpose/Overview
In this programming assignment I created a rudimentary social network. My user-defined `User` and `MyList` classes were implemented along with a supplied `GMLReader` class that was used to populate two empty `vector<string>` objects with node and edge data respectively; these vectors will then be parsed to dynamically create User objects in a list of type `MyList<User*>`. The program additionally has the functionality to read in a command file that allows the adding and removing of friends from each other's `friendList` of type `MyList<int>`. The new social network will then be output in correct GML format after the changes made by the command file as per the instructions of the `GMLWriter` class.


## Requirements
This software must be able to read in a GML file and format it into a `MyList<User*>` object that contains Users. Each user will have information associated with him/her and the program will allow the editing of a User's `friendList` through a command file. The program must then be able to print out to an output file a new correctly formatted GML file with the updated information for every User utilizing the `GMLWriter` class.


## Classes
class `MyList`
+ A templated dynamic array-based list class
+ Member data:
```C++
T *data_;		// The dynamically allocated array of type T that makes up the list
int size_;		// The current size of the list
int capacity_;	// The current capacity of the list (its max size)
```

+ Member functions:
```C++
MyList();					// The default constructor of MyList that creates a dynamic array of size 10
MyList(int capacity);		// A constructor that accepts a specified capacity from the user and creates a dynamic array of size capacity
~MyList();					// Default destructor that deletes data_
void push_back(T item);		// Adds item to the end of data_. If this makes the array too large, the function automatically allocates a new
								// 	  array of size capacity_*2, copies all data to this new array, and deletes the old array
void remove(T item) const;	// Finds and removes the first instance of item from data_ and shifts all succeeding items in data_ down one
T pop(inc loc);				// Removes the item at loc and returns it
T& at(int loc) const;		// Returns a reference to the item at loc in data_
int size() const;			// Returns the size of data_
T& operator[](int loc);		// Used to access and assign data to items at loc
```

class `User`
+ User contains data such as name, age, zip code, and a `friendList` of type `MyList<int>` containing the ID of all their friends
+ Member data:
```C++
string name_;				// The user's name
int id_;					// The user's ID number used to relate users to each other
int age_;					// The user's age
int zip_;					// The user's zip code
MyList<int> friendList_;	// The list of friend ID's linking this user to his/her friends
```

+ Member functions:
```C++
User();											// Default constructor for User that sets id_ to 0, name_ to "", age_ to 0, and zip_ to 0
User(int id, string name, int age, int zip);	// Constructor that takes in user-defined values and sets id_, name_, age_, and zip_
int getId() const;								// Returns the user's id_ number
string getName() const; 						// Returns the user's name_
int getAge() const;								// Returns the user's age_
int getZip() const;								// Returns the user's zip_ code
void addFriend(int id);							// Adds a user of ID number id to current user's friendList_
													//   If user already exists in friendList_, throws an exception
void removeFriend(int id);						// Removes a user of ID number id from current user's friendList_
													//   If user does not exist in friendList_, throws an exception
int getFriends() const;							// Returns the number of friends this User has
int getFriendId(int loc) const;					// Returns the ID number at location loc in User's friendList
```

class `GMLWriter`
+ Class should be able to receive edge and node data from the User list and write it to an output file in correct GML format that should have no problems being read in as input
+ Member data:
```C++
const char* fn_;	// The filename of the output file
```

+ Member functions:
```C++
GMLWriter();										// Constructs a GMLWriter object that sets fn_ to "output.gml"
bool print(const char* fn, MyList<User*>& users);	// Accepts an output filename fn and a list of type MyList<User*> and prints
														//   the corresponding edge and node data in GML format
```

## High-level Architecture
The program accepts all input through input files provided at run-time through the command line. An input `.gml` file is read into two empty `vector<string>` objects by the `GMLReader` class, which represent nodes (users) and edges (the shared friendship between users) respectively.
The user `vector<string>` object is then parsed and used to create User objects that are added to a list of type `MyList<User*>`, whereas the id/friendship `vector<string>` object is parsed through to create friendships between users using the `User` class' `addFriend()` function in a reflexive fashion.
The program then reads in the `.txt` command file and interprets each command, adding or removes friends from each other's `friendList` as necessary in a reflexive fashion.
Lastly, the program will utilize the `GMLWriter` class to output a correctly formatted GML file that reflects the changes made by the command file. This file should be able to be read back in correctly without any issues.


## User Interface
The UI of this program is very simplistic as it is only command prompt based. The user will run the program, providing an input `.gml` file, a command file (`.txt`), and an output `.gml` file in that order.
Initial User objects will be created from the data provided in the input `.gml` file, modified by the `.txt` command file, and finally output into another `.gml` file. A user can change the user data in the input `.gml` file and modify the commands in the command file to produce different results.


##Test Cases
Testing will be done using the provided `test.gml` and `commands.txt` files (in addition to other test cases).
