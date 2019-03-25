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
public:
	NetworkManager() {}
	USERID registerUser(std::string name) {
		memberid++;
		members.insert(std::make_pair(memberid, new Person(name)));
		return memberid;
	}

	void printMembers() {
		std::cout << "members of social network are:" << std::endl;
		for (auto p : members) {
			std::cout << "  -> " << p.first << ": " << p.second->name << std::endl;
		}
	}

};

USERID NetworkManager::memberid = -1;
