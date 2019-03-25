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
	requests.insert(std::make_pair(fr->getSenderName(), fr));
	std::cout << name << " has received an invitation from " << fr->getSenderName() << std::endl;
}

void Person::listRequests(NetworkManager* mgr) {
	mgr->listRequestsForMember(memberid);
}

void Person::listFriends() {
	/*
	std::cout << "Friends of " << name << " based on friends vector are:" << std::endl;
	for (auto fr : friends)  {
		std::cout << "  -> " << fr->name << std::endl;
	}*/
	
	std::cout << "Friends of " << name << " based on relationships vector are:" << std::endl;
	for (auto r : relationships) {
		std::cout << "  -> " << r->getFriendName(name) << std::endl;
	}
	
}

bool Person::isFriendOf(Person* other) {
	if (std::find(friends.begin(), friends.end(), other) != friends.end()) {
		return true;
	}
	return false;
}

void Person::acceptRequestFrom(std::string name, bool eraseReq) {
	if (requests.find(name) != requests.end()) {
		requests[name]->accept();
		friends.push_back(requests[name]->from); // alapbol inaccessible, de ha
		// azt mondjuk, hogy const pointer akkor akar lehet accessible is!
		// requests[name]->from = this; // ilyet meg jo h nem lehet!
		if (eraseReq) {
			requests.erase(name);
		}
	}
}

void Person::acceptAllRequests() {
	std::for_each(requests.begin(), requests.end(),
		[](std::pair<std::string, FriendRequest*> np) {
			//hajjaj, Liskov elv...
			np.second->to->acceptRequestFrom(np.second->from->name, false);
			// ehhez kell az is, hogy ne torljodjon a request azonnal...
		}
	);
	requests.clear();
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

void Person::addRelationship(Relationship* r) {
	relationships.push_back(r);
}

void Person::tagFriend(std::string nameOfFriend) {
	class myFunctor {
	public:
		myFunctor(std::string nof) : friendName(nof) {}
		void operator()(Relationship* r) {
			r->tagFriend(friendName);
		}
	private:
		std::string friendName;
	};
	/*
	std::for_each(relationships.begin(), relationships.end(), 
		[](Relationship* r) {
			r->tagFriend(nameOfFriend);
		}
	);
	*/
	std::for_each(
		relationships.begin(),
		relationships.end(),
		myFunctor(nameOfFriend)
	);
}

void Person::purgeStaleRelationships() {
	class StaleRelationshipsCollector {
	public:
		StaleRelationshipsCollector(std::vector<int>* vec) : cur(0) {
			stale_inxes = vec;
		}
		void operator()(Relationship* r) {
			if (r->isStale()) {
				stale_inxes->push_back(cur);
			}
			cur++;
		}
	private:
		std::vector<int>* stale_inxes;
		int cur;
	};
	// kivulrol kell neki beadni a vektort, hogy utana megmaradjon!
	std::vector<int> stale_indices;
	StaleRelationshipsCollector src(&stale_indices);
	std::for_each(relationships.begin(), relationships.end(), src);
	for (int inx : stale_indices) {
		Relationship* rhandle = relationships[inx]; // a cimet atmasoljuk
		//mivel remove mar torli is a relationships vektorbol!
		relationships[inx]->remove();
		delete rhandle; // itt van a delete... hmm ez nem idealis
		// ez az egesz sokkal szebb lenne egy relationshipManagerrel!
	}
}

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