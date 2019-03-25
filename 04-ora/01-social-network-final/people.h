#pragma once

#include <string>
#include <vector>
#include <map>

class FriendRequest; // fwd declaration, hogy ne kelljen keresztbe hivatkozni...
class Relationship;
class NetworkManager;

class Person {
private:
	NetworkManager * mgrptr;
public:
	Person(std::string n, int id, NetworkManager* mgr) : name{ n }, memberid(id), mgrptr(mgr) {}
	std::string name;
	int memberid;
	std::map <int, FriendRequest*> requests; // egy embertol csak egy request johet!
	std::map <int, Relationship*> relationships; // kivel van a relationship? Ez egy egyedi int! jol keresheto
	// jo ha map-et hasznalunk mert gyorsabban keresheto mint set
	void setRequest(FriendRequest*);
	void listRequests();
	void listFriends();
	void acceptRequestFrom(int);
	void acceptAllRequests();
	void addRelationship(Relationship*);
	void tagFriend(int taggeeid);
	void getStaleRelationships(std::vector<Relationship*>& staleRels);
	void unfriend(int id);
	// void unfriendAndNotifyManager(int id); // todo: calling unfriend directly will not remove it from manager...
};