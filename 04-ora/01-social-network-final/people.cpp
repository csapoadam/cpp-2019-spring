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

void Person::listFriends(NetworkManager* mgr) {
	// todo: store local cache of friends as well...
	mgr->listFriendsOfMember(memberid);
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

void Person::tagFriend(int taggeeid, NetworkManager* mgr) {
	mgr->tag(memberid, taggeeid); // todo: would be better to have relationships at hand...
}

void Person::purgeStaleRelationships(NetworkManager* mgr) {
	mgr->purgeStaleRelationships(memberid);
}


/*
bool Person::isFriendOf(Person* other) {
	if (std::find(friends.begin(), friends.end(), other) != friends.end()) {
		return true;
	}
	return false;
}

void Person::requestAcceptedBy(Person* p) {
	// valami ellenorzes, h tenyleg kuldtunk neki request-et???
	friends.push_back(p);
}

void Person::rejectRequestFrom(std::string name) {
	if (requests.find(name) != requests.end()) {
		requests[name]->reject();
		requests.erase(name);
	}
}
*/

/*
void Person::addRelationship(Relationship* r) {
	relationships.push_back(r);
}
*/

/*
void Person::unfriend(std::string other) {

	class MyPredicate {
	public:
		MyPredicate(std::string o) : other(o) {}
		std::string other;
		bool operator()(Person* p) {
			return p->name == other;
		}
	};

	friends.erase(
		std::remove_if(
			friends.begin(),
			friends.end(),
			MyPredicate(other)),
		friends.end());

	class MyRelationshipPredicate {
	public:
		MyRelationshipPredicate(std::string o) : other(o) {}
		std::string other;
		bool operator()(Relationship* r) {
			// return r->involves(other);
			return true; // do this for time being so that code compiles
		}
	};

	relationships.erase(
		std::remove_if(
			relationships.begin(),
			relationships.end(),
			MyRelationshipPredicate(other)
		),
		relationships.end());
}
*/