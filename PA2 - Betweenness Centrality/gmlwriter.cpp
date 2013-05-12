#include "gmlwriter.h"
#include "mylist.h"
#include <fstream>

GMLWriter::GMLWriter() {
	fn_ = "output.gml";
}

bool GMLWriter::print(const char* fn, MyList<User*>& users) {
	fn_ = fn;
	std::ofstream oFile;
	oFile.open(fn_);
	
	if (!oFile.is_open()) return false; // Return if opening output file failed
	
	oFile << "graph [\n";
	for (int i = 0; i < users.size(); i++) { // Print node data
		oFile << "\tnode [\n";
		oFile << "\t\tid " << (*users[i]).getId() << "\n";
		oFile << "\t\tname \"" << (*users[i]).getName() << "\"\n";
		oFile << "\t\tage " << (*users[i]).getAge() << "\n";
		oFile << "\t\tzip " << (*users[i]).getZip() << "\n";
		oFile << "\t]\n";
	}
	
	for (int i = 0; i < users.size(); i++) { // Print edge data
		for (int j = 0; j < (*users[i]).getFriends(); j++) {
			oFile << "\tedge [\n";
			oFile << "\t\tsource " << (*users[i]).getId() << "\n";
			oFile << "\t\ttarget " << (*users[i]).getFriendId(j) << "\n";
			oFile << "\t]\n";
		}
	}
	oFile << "]";
	
	oFile.close();
	return true;
}
