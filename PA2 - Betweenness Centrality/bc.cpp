#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "gmlreader.h"
#include "bcuser.h"
#include "mylist.h"
#include "bcalg.h"
using namespace std;

int main(int argc, char *argv[]) {
	// Check to see if command line arguments are correct in number
	if(argc != 3) {
		cerr << "Please provide the input GML file and output file" << endl;
		return 0;
	}
	
	
	// Store input GML filename and output .txt filename
	char* iFile = argv[1];
	char* oFile = argv[2];
	
	
	// Instantiate node and edges vectors and call GMLReader class read() function
	GMLReader reader;
	vector<string> nodes;
	vector<string> edges;
	if (!reader.read(iFile, nodes, edges)) { // Quits program if input file cannot be opened
		cerr << "Cannot open GML input file" << endl;
		return 0;	
	}
	
	
	cout << "Making nodes..." << endl;
	// Use stringstream to iterate through nodes vector.
	// Data can be in any order in the input GML file and will be saved correctly based on the value of
	// 	  'string flag'.
	// If nodes contain garbage values, User creation is skipped immediately.
	// Data stored in temp variables, then used to dynamically create a new User object which is added
	//	  to the userList.
	MyList<BCUser*> userList;
	BCUser* tempUser;
	string tempName, flag;
	int infoCounter = 0; // Used to make sure that the four correct pieces of expected information are found before proceeding
	int tempId = 0, tempAge = 0, tempZip = 0;
	for (unsigned int i = 0; i < nodes.size(); i++) {
		stringstream ss(nodes[i], stringstream::in | stringstream::out);
		
		while (infoCounter < 4) {
			ss >> flag;

			if (flag == "id") {
				ss >> tempId;
				if (ss.fail()) {
					cerr << "At line in input GML file: " << flag << endl;
					cerr << "\tbc.cpp:54: Unexpected data type for input." << endl;
					break;
				}
				infoCounter++;
			} else if (flag == "name") {
				ss.ignore(128, '\"');
				getline(ss, tempName, '\"');
				if (ss.fail()) {
					cerr << "At line in input GML file: " << flag << endl;
					cerr << "\tbc.cpp:63: Unexpected data type for input." << endl;
					break;
				}
				infoCounter++;
			} else if (flag == "age") {
				ss >> tempAge;
				if (ss.fail()) {
					cerr << "At line in input GML file: " << flag << endl;
					cerr << "\tbc.cpp:71: Unexpected data type for input." << endl;
					break;
				}
				infoCounter++;
			} else if (flag == "zip") {
				ss >> tempZip;
				if (ss.fail()) {
					cerr << "At line in input GML file: " << flag << endl;
					cerr << "\tbc.cpp:79: Unexpected data type for input." << endl;
					break;
				}
				infoCounter++;
			} else {
				cerr << "At line in input GML file: " << flag << endl;
				cerr << "\tbc.cpp:51: Unrecognized flag." << endl;
			}
		}
		
		if (infoCounter == 4) { // Only make a user if all four expected data members are found correctly
			tempUser = new BCUser(tempId, tempName, tempAge, tempZip);
			userList.push_back(tempUser);
		}
		infoCounter = 0;
	}
	cout << "  --Done -> " << userList.size() << " BCUsers created" << endl;
	
	
	cout << "Making edges..." << endl;
	// Use stringstream to iterate through edges vector.
	// Flag 'target' tells program that following ID should be added to 'source' User's friendList.
	// 'target' and 'source' are interchangeable in GML input file.
	// If garbage line is found, print an error and skip it.
	int tempSource = 0, tempTarget = 0;
	for (unsigned int i = 0; i < edges.size(); i++) {
		stringstream ss(edges[i], stringstream::in | stringstream::out);
		
		while (infoCounter < 2) {
			ss >> flag;
			if (flag == "source") {
				ss >> tempSource;
				infoCounter++;
			} else if (flag == "target") {
				ss >> tempTarget;
				infoCounter++;
			} else {
				cerr << "At line in input GML file: " << flag << endl;
				cerr << "\tbc.cpp:111: Unrecognized flag." << endl;
			}
		}
		
		for (int j = 0; j < userList.size(); j++) {
			if ((*userList[j]).getId() == tempSource) {
				try {
					for (int k = 0; k < userList.size(); k++) {
						if ((*userList[k]).getId() == tempTarget) {
							(*userList[j]).addFriend(tempTarget);
							break;
						}
					}
				} catch (invalid_argument a) { 
					cerr << "Attempt to add User " << tempTarget << " to friendList_ of User " << tempSource << endl;
					cerr << "\t" << a.what() << endl;
				} catch (...) {
					cerr << "Unknown error attempting to add friends while parsing edges." << endl;
				}
				break;
			}
		}
		infoCounter = 0;
	}
	cout << "  --Done" << endl;
	
	
	// Compute BC scores and return normalized BC values
	// !!NOTE!! This code does NOT assume that the ID of a user = that user's index in userList at the cost of a longer runtime.
	//		Running the 1000 User test file should take about 1 (one) minute rather than about 3 (three) seconds if I do make the above assumption.
	MyList<double>* norms;
	try {
		norms = BCAlg::computeBC(userList);
	} catch(invalid_argument a) {
		cerr << a.what() << "\n\tCannot compute normalized BC scores." << endl;
	}
	
	
	cout << "Printing results..." << endl;
	// Print out BC data
	ofstream output;
	output.open(oFile);
	for (int i = 0; i < norms->size(); i++)
		if (norms->at(i) != -1) output << i << " " << norms->at(i) << endl;
	output.close();
	cout << "  --Done" << endl;
	
	// Delete all dynamically created objects before program ends
	for (int i = 0; i < userList.size(); i++) delete userList[i];
	delete norms;
	
	cout << "Program complete." << endl;
	return 1;
}
