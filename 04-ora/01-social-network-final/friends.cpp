#include "stdafx.h"
#include "friends.h"
#include "people.h"

FriendRequest::FriendRequest(Person* f, Person* t): from(f), to(t) {
	isPending = true;
}

FriendRequest::~FriendRequest() {
	std::cout << "deleted friend request from " << from->name << " to " << to->name << "!" << std::endl;
}

std::string FriendRequest::getSenderName(){
	return from->name;
}

void FriendRequest::accept() {
	isAccepted = true;
	isPending = false;
	/*
	from->requestAcceptedBy(to);
	// miutan mar a Relationship-et is modellezzuk
	// elegansabb, ha a FriendRequest jegyzi be a kapcsolatot
	// mindket felnel!
	Relationship* r = new Relationship(to, from); // na ezt erdemes atgondolni - ki
	// fog valaha delete-et hivni ra?
	// ha a kapcsolat megszunik delete-et kell hivni ra!
	from->addRelationship(r);
	to->addRelationship(r);
	*/
}

void FriendRequest::reject() {
	isAccepted = false;
	isPending = false;
}

Relationship::Relationship(Person* persona, Person* personb) : personA(persona), personB(personb) {
	aTaggedBCount = 0;
	bTaggedACount = 0;
}

Relationship::~Relationship() {
	// a nyomonkovethetoseg miatt irassunk ki valamit
	std::cout << "Relationship between " <<
		personA->name << " and " << personB->name << " DESTROYED" << std::endl;
}

Person* Relationship::getFriendOfPersonWithId(int id) {
	if (id == personA->memberid) {
		return personB;
	}
	return personA;
}

void Relationship::tagFriend(std::string taggee) {
	if (personA->name == taggee) {
		std::cout << personB->name << " has tagged " << taggee << std::endl;
		bTaggedACount++;
	}else if (personB->name == taggee){
		std::cout << personA->name << " has tagged " << taggee << std::endl;
		aTaggedBCount++;
	}
}

bool Relationship::isStale() {
	if (aTaggedBCount == 0 && bTaggedACount == 0) {
		std::cout << "relationship between " << personA->name << " and " <<
			personB->name << " is STALE" << std::endl;
	}
	return aTaggedBCount == 0 && bTaggedACount == 0;
}

bool Relationship::involves(int userid) {
	return personA->memberid == userid || personB->memberid == userid;
}

/*
void Relationship::remove() {
	std::cout << "calling unfriend for " << personA->name << " and " << personB->name << std::endl;
	personA->unfriend(personB->name);
	personB->unfriend(personA->name);
}
*/