#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "gmlwriter.h"
#include "gmlreader.h"
#include "user.h"
#include "mylist.h"
using namespace std;

int main(int argc, char *argv[]) {
	// Check to see if command line arguments are correct in number
	if(argc < 4) {
		cerr << "Please provide the input GML file, command file, and output file" << endl;
		return 0;
	}
	
	
	// Store input GML filename, command file filename, output filename
	char* iFile = argv[1];
	char* cFile = argv[2];
	char* oFile = argv[3];
	
	
	// Instantiate node and edges vectors and call GMLReader class read() function
	GMLReader reader;
	vector<string> nodes;
	vector<string> edges;
	if (!reader.read(iFile, nodes, edges)) { // Quits program if input file cannot be opened
		cerr << "Cannot open GML input file" << endl;
		return 0;	
	}
	
	
	// Use stringstream to iterate through nodes vector.
	// Data can be in any order in the input GML file and will be saved correctly based on the value of
	// 	  'string flag'.
	// Data stored in temp variables, then used to dynamically create a new User object which is added
	//	  to the userList.
	MyList<User*> userList;
	User* tempUser;
	string tempName, flag;
	int tempId = 0, tempAge = 0, tempZip = 0;
	for (unsigned int i = 0; i < nodes.size(); i++) {
		stringstream ss(nodes[i], stringstream::in | stringstream::out);
		
		for (int j = 0; j < 4; j++) {
			ss >> flag;
			if (flag == "id") {
				ss >> tempId;
			} else if (flag == "name") {
				ss.ignore(128, '\"');
				getline(ss, tempName, '\"');
			} else if (flag == "age") {
				ss >> tempAge;
			} else if (flag == "zip") {
				ss >> tempZip;
			}
		}
		
		tempUser = new User(tempId, tempName, tempAge, tempZip);
		userList.push_back(tempUser);
	}
	
	
	// Use stringstream to iterate through edges vector.
	// Flag 'target' tells program that following ID should be added to 'source' User's friendList.
	// 'target' and 'source' are interchangeable in GML input file.
	int tempSource = 0, tempTarget = 0;
	for (unsigned int i = 0; i < edges.size(); i++) {
		stringstream ss(edges[i], stringstream::in | stringstream::out);
		
		for (int j = 0; j < 2; j++) {
			ss >> flag;
			if (flag == "source") {
				ss >> tempSource;
			} else if (flag == "target") {
				ss >> tempTarget;
			}
		}
		
		for (int j = 0; j < userList.size(); j++) {
			if ((*userList[j]).getId() == tempSource) {
				try {
					(*userList[j]).addFriend(tempTarget);
				} catch (invalid_argument a) { 
					cerr << "Attempt to add User " << tempTarget << " to friendList_ of User " << tempSource << endl;
					cerr << "\t" << a.what() << endl;
				} catch (...) {
					cerr << "Unknown error attempting to add friends while parsing edges." << endl;
				}
				break;
			}
		}
	}
	
	
	// Read in command file and interpret the 'a' and 'r' flags appropriately.
	// If an unknown flag is found, prints an error.
	string user1 = "", user2 = "", currentLine;
	int tempId1 = -1, tempId2 = -1, tempIndex1 = -1, tempIndex2 = -1;
	ifstream commands;
	commands.open(cFile);
	if (commands.is_open()) { // Will only process command file if it successfully opens
		while (!commands.eof()) {
		getline(commands, currentLine);
			if (commands.good()) {
				stringstream ss(currentLine, stringstream::in | stringstream::out);
			
				ss >> flag;
				ss.ignore(128, '\"');
				getline(ss, user1, '\"');
				ss.ignore(128, '\"');
				getline(ss, user2, '\"');
			
				if (flag == "a") { // Add friends
					for (int i = 0; i < userList.size(); i++) {
						if ((*userList[i]).getName() == user1) {
							tempIndex1 = i;
							tempId1 = (*userList[i]).getId();
						} else if ((*userList[i]).getName() == user2) {
							tempIndex2 = i;
							tempId2 = (*userList[i]).getId();
						}	
					}
					try {
						(*userList[tempIndex1]).addFriend(tempId2);
						(*userList[tempIndex2]).addFriend(tempId1);
					} catch(invalid_argument a) {
						cerr << "At line in command file: " << currentLine << endl;
						cerr << "\t" << a.what() << endl;
						cerr << "\tUser does not exist." << endl;
					} catch(...) {
						cerr << "At line in command file: " << currentLine << "\n\t" << "Unknown error adding friends." << endl;
					}
				} else if (flag == "r") { // Remove friends
					for (int i = 0; i < userList.size(); i++) {
						if ((*userList[i]).getName() == user1) {
							tempIndex1 = i;
							tempId1 = (*userList[i]).getId();
						} else if ((*userList[i]).getName() == user2) {
							tempIndex2 = i;
							tempId2 = (*userList[i]).getId();
						}	
					}
					try {
						(*userList[tempIndex1]).removeFriend(tempId2);
						(*userList[tempIndex2]).removeFriend(tempId1);
					} catch(invalid_argument a) {
						cerr << "At line in command file: " << currentLine << endl;
						cerr << "\t" << a.what() << endl;
						cerr << "\tUser does not exist." << endl;
					} catch(...) {
						cerr << "At line in command file: " << currentLine << "\n\t" << "Unknown error removing friends." << endl;
					}
				} else {
					cerr << "At line in command file: " << currentLine << endl;
					cerr << "\tUnrecognized command." << endl;
				}
			}
			tempId1 = -1;		// Reset all temp variables to detect errors in next line of command file
			tempId2 = -1;
			tempIndex1 = -1;
			tempIndex2 = -1;
		}
	} else cerr << "Cannot open the command file" << endl;
	commands.close();
	
	
	
	// Create a GMLWriter object and call print() to print out current userList data in GML format.
	// Output an error if the writing fails.
	GMLWriter writer;
	if (!writer.print(oFile, userList)) {
		cerr << "Output to file failed." << endl;
	}
	
	// Delete all created users before program ends
	for (int i = 0; i < userList.size(); i++) {
		delete userList[i];
	}
	
	return 1;
}
