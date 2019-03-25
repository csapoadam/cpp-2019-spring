// SocialNetwork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "networkmanager.h"
// #include "people.h"
// #include "friends.h"
#include <iostream>

int main()
{
	NetworkManager netmgr;
	int belaid = netmgr.registerUser("Bela");
	int panniid = netmgr.registerUser("Panni");
	int fanniid = netmgr.registerUser("Fanni");
	int sandorid = netmgr.registerUser("Sandor");
	netmgr.printMembers();

	Person* bela = netmgr.getUserById(belaid);
	if (bela) {
		bela->sendRequestTo(panniid, &netmgr);
		bela->sendRequestTo(panniid, &netmgr); // should print request already sent...
	}

	Person* panni = netmgr.getUserById(panniid);
	if (panni) {
		panni->listRequests(&netmgr);
	}

	/*
	FriendRequest req1(&p1, &p2);
	// idempotens, ugye?
	FriendRequest req2(&p1, &p2);
	p2.listRequests(); // hupsz, elfelejtettuk?
	// FriendRequest req3(&p3, &p3); //autofriend nem mukodhet
	FriendRequest(&p3, &p2);
	p1.listRequests();
	p2.listRequests();
	p3.listRequests();
	std::cout << std::endl;
	p1.listFriends();
	p2.listFriends();
	p3.listFriends();
	std::cout << std::endl;

	//std::cout << p2.name << " will now accept request from " << p3.name << std::endl;
	//p2.acceptRequestFrom(p3.name);

	
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

