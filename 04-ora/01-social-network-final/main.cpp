// SocialNetwork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "networkmanager.h"
// #include "people.h"
// #include "friends.h"
#include <iostream>
#include <vector>

void printState(std::vector<Person*> users, NetworkManager* netmgr) {
	for (auto p : users) {
		p->listRequests(netmgr);
	}
	std::cout << std::endl;
	for (auto p : users) {
		p->listFriends(netmgr);
	}
	std::cout << std::endl;
}


int main()
{
	NetworkManager netmgr;
	int belaid = netmgr.registerUser("Bela");
	int panniid = netmgr.registerUser("Panni");
	int fanniid = netmgr.registerUser("Fanni");
	int sandorid = netmgr.registerUser("Sandor");
	netmgr.printMembers();

	Person* bela = netmgr.getUserById(belaid);
	Person* panni = netmgr.getUserById(panniid);
	Person* fanni = netmgr.getUserById(fanniid);
	Person* sandor = netmgr.getUserById(sandorid);

	if (bela) {
		bela->sendRequestTo(panniid, &netmgr);
		bela->sendRequestTo(panniid, &netmgr); // should print request already sent...
		bela->sendRequestTo(belaid, &netmgr); // cannot send to oneself
		bela->sendRequestTo(15, &netmgr); // no such user w/ id of 15
	}

	if (fanni) {
		fanni->sendRequestTo(panniid, &netmgr);
	}

	if (bela && panni && fanni) {
		std::vector<Person*> myusers = {bela, panni, fanni};

		printState(myusers, &netmgr);

		std::cout << panni->name << " will now accept request from " << bela->name << std::endl;
		panni->acceptRequestFrom(belaid, &netmgr);
		std::cout << std::endl;
		std::cout << "so we now have:" << std::endl;
		printState(myusers, &netmgr);

		// now test that neither bela nor panni can send request to each other any longer!
		bela->sendRequestTo(panniid, &netmgr);
		panni->sendRequestTo(belaid, &netmgr);
		printState(myusers, &netmgr);// good
	}

	/*
	

	
	std::cout << p2.name << " will now accept all requests" << std::endl;
	p2.acceptAllRequests();
	

	std::cout << "Let's say " << p2.name << " now sends a friend request to " << p3.name << std::endl;
	FriendRequest(&p2, &p3); // mar egymas baratai, nem szabad engedni!
	std::cout << ".. and vice versa" << std::endl;
	FriendRequest(&p3, &p2); // mar egymas baratai, nem szabad engedni!

	p1.listRequests();
	p2.listRequests();
	p3.listRequests();
	std::cout << std::endl;
	p1.listFriends();
	p2.listFriends();
	p3.listFriends();


	std::cout << "Let's say " << p3.name << " now tags " << p2.name << std::endl;
	p3.tagFriend(p2.name);

	std::cout << "Let's say " << p2.name << " now purges stale relationships" << std::endl;
	p2.purgeStaleRelationships();

	std::cout << std::endl;
	p1.listFriends();
	p2.listFriends();
	p3.listFriends();
	*/

	std::cin.get();
    return 0;
}

