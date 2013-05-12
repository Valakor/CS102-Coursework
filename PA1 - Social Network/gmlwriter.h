#ifndef GML_WRITER_H
#define GML_WRITER_H
#include "user.h"

class GMLWriter {
public:
	GMLWriter();										// Default constructor that sets 'fn_' to "output.gml"
	bool print(const char* fn, MyList<User*>& users);	// Prints all User data in 'users' in correct GML format to a file with filename 'fn'. Returns true if successful, false otherwise
private:
	const char* fn_;									// Filename of output file
};

#endif
