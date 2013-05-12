#ifndef BCUSER_H
#define BCUSER_H
#include "user.h"

class BCUser: public User {
public:
	BCUser();											// Default constructor that calls default constructor of User and sets all BC data to default values
	BCUser(int id, std::string name, int age, int zip);	// Constructor that calls the same overloaded constructor in User and sets all BC data to defualt values
	~BCUser();											// Destructor that deletes the predecessor List
	int dist;			// distance to current source vertex
	int numsp;			// number of shortest paths
	MyList<int>* preds;	// List of predecessors
	double delta;		// partial BC score
	double bc;			// total BC score
};

#endif
