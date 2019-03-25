#pragma once

#include <string>
#include <vector>
#include <map>

class FriendRequest; // fwd declaration, hogy ne kelljen keresztbe hivatkozni...
class Relationship;

class Person {
public:
	Person(std::string n) : name{ n } {}
	std::string name;
	std::vector<Person*> friends; // baratok sorrendben vannak
	std::vector<Relationship*> relationships; // alternativa: kapcsolatokat taroljunk...
	// igy megtudhatjuk ki volt az elso, masodik, stb.
	// ha torlunk elemet, beallithatjuk nullptr-re, igy a torles is hatekony,
	// a maradek baratnal nem modosul, hogy ki a hanyadik!
	std::map <std::string, FriendRequest*> requests; // egy embertol csak egy request johet!
	// jo ha map-et hasznalunk mert gyorsabban keresheto mint set
	void setRequest(FriendRequest*);
	void listRequests();
	void listFriends();
	bool isFriendOf(Person*);
	void acceptRequestFrom(std::string, bool eraseReq = true);
	void rejectRequestFrom(std::string);
	void acceptAllRequests();
	void requestAcceptedBy(Person*);
	void addRelationship(Relationship*);
	void tagFriend(std::string);
	void purgeStaleRelationships();
	void unfriend(std::string);
};