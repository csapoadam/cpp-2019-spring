#include "stdafx.h"
#include "networkmanager.h"
#include "people.h"
#include "friends.h"

USERID NetworkManager::memberid = -1;
NetworkManager* NetworkManager::instance = nullptr;

USERID NetworkManager::registerUser(std::string name) {
	memberid++;
	members.insert(std::make_pair(memberid, new Person(name, memberid, this)));
	return memberid;
}

void NetworkManager::printMembers() {
	std::cout << "members of social network are:" << std::endl;
	for (auto p : members) {
		std::cout << "  -> " << p.first << ": " << p.second->name << std::endl;
	}
}

void NetworkManager::printState() {
	for (auto p : members) {
		p.second->listRequests();
	}
	std::cout << std::endl;
	for (auto p : members) {
		p.second->listFriends();
	}
	std::cout << std::endl;
}

Person* NetworkManager::getUserById(USERID id) {
	auto pos = members.find(id);
	if (pos != members.end()) {
		return (*pos).second;
	}
	return nullptr;
}

bool NetworkManager::areFriends(USERID ida, USERID idb) {
	for (auto p : relationships) {
		if (p->involves(ida) && p->involves(idb)) {
			return true;
		}
	}
	return false;
}

bool NetworkManager::wasRequestSentByXToY(USERID fromid, USERID toid) {
	for (auto r : requests) {
		if (r->from->memberid == fromid && r->to->memberid == toid) {
			return true;
		}
	}
	return false;
}

void NetworkManager::createRequest(USERID sender, USERID receiver) {
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

void NetworkManager::acceptRequest(FriendRequest* fr) {
	fr->accept();
	Relationship* r = new Relationship(fr->from, fr->to);
	relationships.insert(r);
	fr->from->addRelationship(r);
	fr->to->addRelationship(r);

	auto pos = requests.find(fr);
	if (pos != requests.end()) {
		requests.erase(pos);
	}

	delete fr; // test: without this line, memory not freed!

}

void NetworkManager::acceptAllRequests(USERID who) {
	Person* user = getUserById(who);
	if (user) {
		user->acceptAllRequests();
	}
}

void NetworkManager::tag(USERID whotags, USERID whom) {
	Person* user = getUserById(whotags);
	if (user) {
		user->tagFriend(whom);
	}
}

void NetworkManager::acceptRequest(USERID receiver, USERID sender) {
	Person* recver = getUserById(receiver);
	if (recver) {
		recver->acceptRequestFrom(sender);
	}
}

void NetworkManager::purgeStaleRelationships(USERID whoseRelationships) {
	Person* user = getUserById(whoseRelationships);
	if (user) {
		std::vector<Relationship*> topurge;
		user->getStaleRelationships(topurge);
		for (auto r : topurge) {
			auto pos = relationships.find(r);
			if (pos != relationships.end()) {
				relationships.erase(pos);
			}
			std::pair<Person*, Person*> p = r->getPair();
			p.first->unfriend(p.second->memberid);
			p.second->unfriend(p.first->memberid);
			delete r; // try commented out too!
		}
	}
}
