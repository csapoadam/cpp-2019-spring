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
	// jo ha map-et hasznalunk mert gyorsabban keresheto mint set
	void sendRequestTo(int otherUserId, NetworkManager* mgr);
	void setRequest(FriendRequest*);
	void listRequests(NetworkManager*);
	void listFriends(NetworkManager*);
	void acceptRequestFrom(int, NetworkManager*);
	void acceptAllRequests(NetworkManager*);
	void tagFriend(int taggeeid, NetworkManager* mgr);
	void purgeStaleRelationships(NetworkManager* mgr);
};