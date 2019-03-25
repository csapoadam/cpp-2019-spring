#pragma once

#include <string>
#include <vector>
#include <map>

class FriendRequest; // fwd declaration, hogy ne kelljen keresztbe hivatkozni...
class Relationship;
class NetworkManager;

class Person {
public:
	Person(std::string n, int id) : name{ n }, memberid(id) {}
	std::string name;
	int memberid;
	std::map <int, FriendRequest*> requests; // egy embertol csak egy request johet!
	std::map <int, Relationship*> relationships; // kivel van a relationship? Ez egy egyedi int! jol keresheto
	// jo ha map-et hasznalunk mert gyorsabban keresheto mint set
	void sendRequestTo(int otherUserId, NetworkManager* mgr);
	void setRequest(FriendRequest*);
	void listRequests();
	void listFriends();
	void acceptRequestFrom(int, NetworkManager*);
	void acceptAllRequests(NetworkManager*);
	void addRelationship(Relationship*);
	void tagFriend(int taggeeid);
	void purgeStaleRelationships(NetworkManager* mgr);
	void unfriend(int id);
};