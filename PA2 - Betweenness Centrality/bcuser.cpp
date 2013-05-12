#include "bcuser.h"

BCUser::BCUser():User() {
	dist = -1;
	numsp = 0;
	delta = 0;
	bc = 0;
	preds = new MyList<int>;
}

BCUser::BCUser(int id, std::string name, int age, int zip):User(id, name, age, zip) {
	dist = -1;
	numsp = 0;
	delta = 0;
	bc = 0;
	preds = new MyList<int>;
}

BCUser::~BCUser() {
	delete preds;
}
