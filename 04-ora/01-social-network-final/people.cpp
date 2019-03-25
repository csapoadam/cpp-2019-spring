#include "stdafx.h"
#include "people.h"
#include "friends.h"
#include "networkmanager.h"
#include <utility>
#include <algorithm>


void Person::sendRequestTo(int otherUserId) {
	mgrptr->createRequest(memberid, otherUserId);
}

void Person::setRequest(FriendRequest* fr) {
	requests.insert(std::make_pair(fr->from->memberid, fr));
	std::cout << name << " has received an invitation from " << fr->getSenderName() << std::endl;
}

void Person::listRequests() {
	std::cout << "Requests received by " << name << " are:" << std::endl;
	for (auto p : requests) {
		std::cout << "  -> from " << p.second->from->memberid << ": " << p.second->from->name << std::endl;
	}
}

void Person::listFriends() {
	std::cout << "Friends of " << name << " are:" << std::endl;
	for (auto r : relationships) {
		Person* other = r.second->getFriendOfPersonWithId(memberid);
		std::cout << "  -> " << other->name << std::endl;
	}
}

void Person::acceptRequestFrom(int fromid) {
	if (requests.find(fromid) != requests.end()) {
		FriendRequest* req = requests[fromid];
		requests.erase(fromid);
		mgrptr->acceptRequest(req);
	}
}

void Person::acceptAllRequests() {
	struct RequestAcceptor {
		NetworkManager* mgrp;
		RequestAcceptor(NetworkManager* mgrp) : mgrp(mgrp) {}
		void operator()(std::pair<int, FriendRequest*> p) {
			mgrp->acceptRequest(p.second);
		}
	};

	std::for_each(requests.begin(), requests.end(), RequestAcceptor(mgrptr));
	requests.clear();
}

void Person::addRelationship(Relationship* r) {
	Person* other = r->getFriendOfPersonWithId(memberid);
	int otherid = other->memberid;
	relationships.insert(std::make_pair(otherid, r));
}

void Person::tagFriend(int taggeeid) {
	for (auto p : relationships) {
		Relationship* r = p.second;
		if (r->involves(taggeeid)) {
			r->tagFriend(taggeeid);
		}
	}
}

void Person::purgeStaleRelationships() {
	mgrptr->purgeStaleRelationships(memberid);
}

void Person::unfriend(int id) {
	relationships.erase(id);
}
