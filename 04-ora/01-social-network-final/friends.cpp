#include "stdafx.h"
#include "friends.h"
#include "people.h"

FriendRequest::FriendRequest(Person* f, Person* t): from(f), to(t) {
	if (from == nullptr || to == nullptr) {
		std::cerr << "Invalid friend request" << std::endl;
	}
	// senki sem kuldhet maganak
	else if (from == to) {
		std::cerr << "Cannot autofriend, silly miss Lizzy!" << std::endl;
	}
	// ha mar baratok, nem kuldhet requestet
	else if (to->isFriendOf(from)) {
		std::cerr << to->name << " and " << from->name << " are already friends!" << std::endl;
	}
	else {
		isPending = true;
		to->setRequest(this);
	}
}

std::string FriendRequest::getSenderName(){
	return from->name;
}

void FriendRequest::accept() {
	isAccepted = true;
	isPending = false;
	from->requestAcceptedBy(to);
	// miutan mar a Relationship-et is modellezzuk
	// elegansabb, ha a FriendRequest jegyzi be a kapcsolatot
	// mindket felnel!
	Relationship* r = new Relationship(to, from); // na ezt erdemes atgondolni - ki
	// fog valaha delete-et hivni ra?
	// ha a kapcsolat megszunik delete-et kell hivni ra!
	from->addRelationship(r);
	to->addRelationship(r);
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

std::string Relationship::getFriendName(std::string other) {
	if (other == personA->name) {
		return personB->name;
	}
	return personA->name;
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

bool Relationship::involves(std::string name) {
	return personA->name == name || personB->name == name;
}

void Relationship::remove() {
	std::cout << "calling unfriend for " << personA->name << " and " << personB->name << std::endl;
	personA->unfriend(personB->name);
	personB->unfriend(personA->name);
}