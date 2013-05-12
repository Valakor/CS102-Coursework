#include "bcalg.h"
#include "mylist.h"
#include "queue.h"
#include "stack.h"
#include <stdexcept>

MyList<double>* BCAlg::computeBC(MyList<BCUser*> &userList) {
	if (userList.size() <= 0)
		throw std::invalid_argument("bcalg.cpp:8: userList is emtpy.");
		
		
	// Efficiency determination:	
	// Determine whether or not the ID's in the userList are sequential and equal to the index they are stored at.
	// This code determines whether or not to make the above assumption, and changes what code is run in the BCAlgorithm below.
	bool ordered = true;
	for (int i = 0; i < userList.size(); i++)
		if (userList[i]->getId() != i) { ordered = false; break; }
	
	
	std::cout << "Computing BC scores..." << std::endl;
	if (!ordered) std::cout << "  --Warning: List not ordered. This might take a while..." << std::endl;
	// Parse through all BCUsers in userList and compute total BC scores
	Queue<BCUser*>* Q = new Queue<BCUser*>;
	Stack<BCUser*>* St = new Stack<BCUser*>;
	for (int s = 0; s < userList.size(); s++) { 		// Pick a source node to perform a traversal
		BCUser* tempUser;
		for (int t = 0; t < userList.size(); t++) {		// Initialize all vertex scores/value to prepare for traversal
			tempUser = userList[t];
			delete tempUser->preds;
			tempUser->preds = new MyList<int>;
			tempUser->numsp = 0;
			tempUser->dist = -1;
			tempUser->delta = 0;
		}
		
		userList[s]->numsp = 1;
		userList[s]->dist = 0;
		Q->push_back(userList[s]);
		
		BCUser* v;
		BCUser* w;
		
		// Perform breadth first traversal rooted at s
		while(!Q->empty()) {
			v = Q->front();
			Q->pop_front();
			St->push(v);
			for (int i = 0; i < v->getFriends(); i++) {
				int tempFriendId = v->getFriendId(i);
				
				if (ordered) {	// If efficiency determination determines that the userList is ordered, simply go directly to the index in userList
					w = userList[tempFriendId];
				} else {		// If efficiency determination determines that the userList is not ordered, find the user with given ID
					for (int j = 0; j < userList.size(); j++)
						if (userList[j]->getId() == tempFriendId) { w = userList[j]; break; }
				}
			
				if (w->dist == -1) {
					Q->push_back(w);
					w->dist = v->dist + 1;
				}
				if (w->dist == v->dist + 1) {
					w->numsp = w->numsp + v->numsp;
					w->preds->push_back(v->getId());
				}
			}
		}
		
		// Walk BFS tree back up to collect scores
		while(!St->empty()) {
			w = St->top();
			St->pop();
			
			for (int p = 0; p < w->preds->size(); p++) {
				int tempFriendId = w->preds->at(p);
				
				if (ordered) {	// If efficiency determination determines that the userList is ordered, simply go directly to the index in userList
					v = userList[tempFriendId];
				} else {		// If efficiency determination determines that the userList is not ordered, find the user with given ID
					for (int j = 0; j < userList.size(); j++)
						if (userList[j]->getId() == tempFriendId) { v = userList[j]; break; }
				}
				v->delta = v->delta + ((double)v->numsp/w->numsp)*(1 + w->delta);
			}
			w->bc = w->bc + w->delta;
		}
	}
	delete Q;
	delete St;
	std::cout << "  --Done" << std::endl;
	
	
	std::cout << "Normalizing BC scores..." << std::endl;
	// Calculate Norms of BC values
	MyList<double>* normals = new MyList<double>;
	double max = userList[0]->bc;
	double min = max;
	double score_difference = 0;
	int largestId = 0;
	
	// Find the largest ID in userList
	for (int i = 0; i < userList.size(); i++)
		if (userList[i]->getId() > largestId) largestId = userList[i]->getId();
	
	
	// Initialize normals array to -1
	for (int i = 0; i < largestId + 1; i++)
		normals->push_back(-1);
	
	
	// Find max and min, and set normals array to non-normalized bc values
	double tempBC = -1;
	for (int i = 0; i < userList.size(); i++) {
		tempBC = userList[i]->bc;
		if (tempBC < min) min = tempBC;
		if (tempBC > max) max = tempBC;
		(*normals)[userList[i]->getId()] = tempBC;
	}
	
	
	// Normalize BC scores
	score_difference = max - min;
	std::cout << "  --Max: " << max << ", Min: " << min << ", Diff: " << score_difference << std::endl;
	for (int i = 0; i < largestId + 1; i++)
		if ((*normals)[i] != -1) (*normals)[i] = ((*normals)[i] - min) / (score_difference);
	
	
	std::cout << "  --Done" << std::endl;
	return normals;
}
