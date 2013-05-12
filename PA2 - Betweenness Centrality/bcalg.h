#ifndef BCALG_H
#define BCALG_H
#include "mylist.h"
#include "bcuser.h"

class BCAlg {
public:
	static MyList<double>* computeBC(MyList<BCUser*> &userList); // Calculate all BC values and return a normalized List of all values
};

#endif
