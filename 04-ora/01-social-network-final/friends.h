#pragma once

#include <iostream>
class Person;

class FriendRequest {
public:
	FriendRequest(Person* from, Person* to);
	~FriendRequest();
	std::string getSenderName();
	void accept();
	void reject();
	Person* const from; // konstans pointer, ami Personra mutat
	Person* const to;
private:
	// Person* from;
	// Person* to;
	bool isPending;
	bool isAccepted;
};

// Egy jobb otlet: modellezzuk a kapcsolatot is egy osztallyal.
// Igy nyomon kovetheto, ki kit hanyszor taggelt, hanyszor uzent neki stb.
class Relationship {
public:
	Relationship(Person*, Person*);
	~Relationship();
	Person* getFriendOfPersonWithId(int id);
	std::pair<Person*, Person*> getPair();
	void tagFriend(int taggeeid);
	bool isStale(); // stale relationship, haha
	bool involves(int userid);
private:
	Person* const personA;
	Person* const personB;
	int aTaggedBCount;
	int bTaggedACount;
};