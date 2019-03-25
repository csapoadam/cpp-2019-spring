#include "stdafx.h"
#include "people.h"
#include "friends.h"
#include "networkmanager.h"
#include <utility>
#include <algorithm>


void Person::sendRequestTo(int otherUserId, NetworkManager* mgr) {
	mgr->createRequest(memberid, otherUserId);
}

void Person::setRequest(FriendRequest* fr) {
	requests.insert(std::make_pair(fr->from->memberid, fr));
	std::cout << name << " has received an invitation from " << fr->getSenderName() << std::endl;
}

void Person::listRequests(NetworkManager* mgr) {
	mgr->listRequestsForMember(memberid);
}

void Person::listFriends() {
	std::cout << "Friends of " << name << " are:" << std::endl;
	for (auto r : relationships) {
		Person* other = r.second->getFriendOfPersonWithId(memberid);
		std::cout << "  -> " << other->name << std::endl;
	}
}

void Person::acceptRequestFrom(int fromid, NetworkManager* mgr) {
	if (requests.find(fromid) != requests.end()) {
		FriendRequest* req = requests[fromid];
		requests.erase(fromid);
		mgr->acceptRequest(req);
	}
}

void Person::acceptAllRequests(NetworkManager* mgr) {
	struct RequestAcceptor {
		NetworkManager* mgrp;
		RequestAcceptor(NetworkManager* mgrp) : mgrp(mgrp) {}
		void operator()(std::pair<int, FriendRequest*> p) {
			mgrp->acceptRequest(p.second);
		}
	};

	std::for_each(requests.begin(), requests.end(), RequestAcceptor(mgr));
	requests.clear();
}

void Person::addRelationship(Relationship* r) {
	Person* other = r->getFriendOfPersonWithId(memberid);
	int otherid = other->memberid;
	relationships.insert(std::make_pair(otherid, r));
}

void Person::tagFriend(int taggeeid, NetworkManager* mgr) {
	mgr->tag(memberid, taggeeid); // todo: would be better to have relationships at hand...
}

void Person::purgeStaleRelationships(NetworkManager* mgr) {
	mgr->purgeStaleRelationships(memberid);
}

void Person::unfriend(int id) {
	relationships.erase(id);
}
