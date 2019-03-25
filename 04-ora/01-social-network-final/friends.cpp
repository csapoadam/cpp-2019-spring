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

std::pair<Person*, Person*> Relationship::getPair() {
	return std::make_pair(personA, personB);
}

void Relationship::tagFriend(int taggeeid) {
	if (personA->memberid == taggeeid) {
		std::cout << personB->name << " has tagged " << personA->name << std::endl;
		bTaggedACount++;
	}else if (personB->memberid == taggeeid){
		std::cout << personA->name << " has tagged " << personB->name << std::endl;
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
