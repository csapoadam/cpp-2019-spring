#pragma once

#include <set>
#include <map>
#include <string>

typedef int USERID;
class Person;
class Relationship;
class FriendRequest;

class NetworkManager {
private:
	std::map<USERID, Person*> members;
	std::set<Relationship*> relationships;
	std::set<FriendRequest*> requests;
	static USERID memberid;
	static NetworkManager* instance;

	NetworkManager() {}
	bool areFriends(USERID, USERID);
	bool wasRequestSentByXToY(USERID, USERID);
public:
	static NetworkManager* getInstance()
	{
		if (!instance) {
			instance = new NetworkManager();
		}
		return instance;
	}
	USERID registerUser(std::string name);
	void printMembers();
	void printState();
	Person* getUserById(USERID id);
	void createRequest(USERID sender, USERID receiver);
	void acceptRequest(FriendRequest* fr);
	void acceptRequest(USERID receiver, USERID sender);
	void acceptAllRequests(USERID who);
	void tag(USERID whotags, USERID whom);
	void purgeStaleRelationships(USERID whoseRelationships);
};

