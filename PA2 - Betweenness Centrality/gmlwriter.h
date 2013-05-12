#ifndef GML_WRITER_H
#define GML_WRITER_H
#include "user.h"

class GMLWriter {
public:
	GMLWriter();										// Default constructor that sets 'fn_' to "output.gml"
	bool print(const char* fn, MyList<User*>& users);	// Prints User data in correct GML format
private:
	const char* fn_;									// Filename of output file
};

#endif
