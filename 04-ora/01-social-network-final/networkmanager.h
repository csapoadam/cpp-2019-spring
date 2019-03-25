#pragma once

#include "people.h"
#include "friends.h"
#include <set>
#include <map>
#include <string>

typedef int USERID;

class NetworkManager {
private:
	std::map<USERID, Person*> members;
	std::set<Relationship*> relationships;
	std::set<FriendRequest*> requests;
	static USERID memberid;

	bool areFriends(USERID, USERID);
	bool wasRequestSentByXToY(USERID, USERID);
public:
	NetworkManager() {}
	USERID registerUser(std::string name);
	void printMembers();
	Person* getUserById(USERID id);
	void createRequest(USERID sender, USERID receiver);
	void acceptRequest(FriendRequest* fr);
	void purgeStaleRelationships(USERID whoseRelationships);
};

