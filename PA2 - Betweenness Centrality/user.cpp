#include "user.h"

User::User(): id_(0), name_(""), age_(0), zip_(0) { }

User::User(int id, std::string name, int age, int zip): id_(id), name_(name), age_(age), zip_(zip) { }

int User::getId() const {
	return id_;
}

std::string User::getName() const {
	return name_;
}

int User::getAge() const {
	return age_;
}

int User::getZip() const {
	return zip_;
}

void User::addFriend(int id) {
	for (int i = 0; i < friendList_.size(); i++) {
		if (friendList_[i] == id) throw std::invalid_argument("user.h:25: Friend of this id already exists");
	}
	friendList_.push_back(id);
}


void User::removeFriend(int id) {
	if (!friendList_.remove(id)) throw std::invalid_argument("user.h:32: Friend of this id does not exist");
}

int User::getFriends() const {
	return friendList_.size();
}

int User::getFriendId(int loc) const {
	if (loc < 0 || loc >= friendList_.size()) throw std::invalid_argument("Index out of bounds at call to \'getFriendId\'.");
	return friendList_.at(loc);
}
