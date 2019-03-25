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
		members.insert(std::make_pair(memberid, new Person(name, memberid)));
		return memberid;
	}

	void printMembers() {
		std::cout << "members of social network are:" << std::endl;
		for (auto p : members) {
			std::cout << "  -> " << p.first << ": " << p.second->name << std::endl;
		}
	}

	void listRequestsForMember(USERID id) {
		Person* member = getUserById(id);
		if (member) {
			std::cout << "Requests received by " << member->name << " are:" << std::endl;
			for (auto req : requests) {
				if (req->to == member) {
					std::cout << "  -> from " << req->from->memberid << ": " << req->from->name << std::endl;
				}
			}
		}
	}

	void listFriendsOfMember(USERID id) {
		Person* member = getUserById(id);
		if (member) {
			std::cout << "Friends of " << member->name << " are:" << std::endl;
			for (auto r : relationships) {
				if (r->involves(id)) {
					Person* other = r->getFriendOfPersonWithId(id);
					std::cout << "  -> " << other->name << std::endl;
				}
			}
		}
	}

	Person* getUserById(USERID id) {
		auto pos = members.find(id);
		if (pos != members.end()) {
			return (*pos).second;
		}
		return nullptr;
	}

	bool areFriends(USERID ida, USERID idb) {
		for (auto p : relationships) {
			if (p->involves(ida) && p->involves(idb)) {
				return true;
			}
		}
		return false;
	}

	bool wasRequestSentByXToY(USERID fromid, USERID toid) {
		for (auto r : requests) {
			if (r->from->memberid == fromid && r->to->memberid == toid) {
				return true;
			}
		}
		return false;
	}

	void createRequest(USERID sender, USERID receiver) {
		Person* from = getUserById(sender);
		Person* to = getUserById(receiver);
		if (!from) {
			std::cerr << "Invalid request. Sender does not exist" << std::endl;
			return;
		}
		if (!to) {
			std::cerr << "Invalid request. Receiver does not exist" << std::endl;
			return;
		}
		if (from == to) {
			std::cerr << "Cannot friend yourself!" << std::endl;
			return;
		}
		if (areFriends(sender, receiver)) {
			std::cerr << from->name << " and " << to->name << " are already friends" << std::endl;
			return;
		}
		if (wasRequestSentByXToY(sender, receiver)) {
			std::cerr << "Request has already been sent from " << from->name << " to " << to->name << std::endl;
			return;
		}

		FriendRequest* fr = new FriendRequest(from, to);
		requests.insert(fr);
		to->setRequest(fr);
	}

	void acceptRequest(FriendRequest* fr) {
		fr->accept();
		Relationship* r = new Relationship(fr->from, fr->to);
		relationships.insert(r);

		auto pos = requests.find(fr);
		if (pos != requests.end()) {
			requests.erase(pos);
		}
		
		delete fr; // test: without this line, memory not freed!

	}

	void tag(USERID tagger, USERID taggee) {
		for (auto r : relationships) {
			if (r->involves(tagger) && r->involves(taggee)) {
				r->tagFriend(taggee);
			}
		}
	}

	void purgeStaleRelationships(USERID whoseRelationships) {
		std::vector<Relationship*> relationshipsToPurge;

		for (auto r : relationships) {
			if (r->involves(whoseRelationships) && r->isStale()) {
				relationshipsToPurge.push_back(r);
			}
		}

		for (auto r : relationshipsToPurge) {
			auto pos = relationships.find(r);
			if (pos != relationships.end()) {
				relationships.erase(pos);
			}
			delete r; // try commented out too!
		}
	}

};

