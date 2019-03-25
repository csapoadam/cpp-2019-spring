// SocialNetwork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "networkmanager.h"
// #include "people.h"
// #include "friends.h"
#include <iostream>
#include <vector>

void printState(std::vector<Person*> users) {
	for (auto p : users) {
		p->listRequests();
	}
	std::cout << std::endl;
	for (auto p : users) {
		p->listFriends();
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

		printState(myusers);

		//std::cout << panni->name << " will now accept request from " << bela->name << std::endl;
		//panni->acceptRequestFrom(belaid, &netmgr);
		std::cout << panni->name << " will now accept all requests" << std::endl;
		panni->acceptAllRequests(&netmgr);
		std::cout << std::endl;
		std::cout << "so we now have:" << std::endl;
		printState(myusers);

		// now test that neither bela nor panni can send request to each other any longer!
		bela->sendRequestTo(panniid, &netmgr);
		panni->sendRequestTo(belaid, &netmgr);
		printState(myusers);// good

		std::cout << "Let's say " << fanni->name << " now tags " << panni->name << std::endl;
		fanni->tagFriend(panniid);

		std::cout << "Let's say " << panni->name << " now purges stale relationships" << std::endl;
		panni->purgeStaleRelationships(&netmgr); // should remove Bela

		printState(myusers);
	}

	std::cin.get();
    return 0;
}

