// SocialNetwork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "networkmanager.h"
#include "people.h"
#include <iostream>
#include <vector>

void printState() {
	NetworkManager* m = NetworkManager::getInstance();
	m->printState();
}


int main()
{
	NetworkManager* netmgr = NetworkManager::getInstance();
	int belaid = netmgr->registerUser("Bela");
	int panniid = netmgr->registerUser("Panni");
	int fanniid = netmgr->registerUser("Fanni");
	int sandorid = netmgr->registerUser("Sandor");
	netmgr->printMembers();

	Person* bela = netmgr->getUserById(belaid);
	Person* panni = netmgr->getUserById(panniid);
	Person* fanni = netmgr->getUserById(fanniid);
	Person* sandor = netmgr->getUserById(sandorid);

	if (bela) {
		bela->sendRequestTo(panniid);
		bela->sendRequestTo(panniid); // should print request already sent...
		bela->sendRequestTo(belaid); // cannot send to oneself
		bela->sendRequestTo(15); // no such user w/ id of 15
	}

	if (fanni) {
		fanni->sendRequestTo(panniid);
	}

	if (bela && panni && fanni) {
		printState();

		//std::cout << panni->name << " will now accept request from " << bela->name << std::endl;
		//panni->acceptRequestFrom(belaid, &netmgr);
		std::cout << panni->name << " will now accept all requests" << std::endl;
		panni->acceptAllRequests();
		std::cout << std::endl;
		std::cout << "so we now have:" << std::endl;
		printState();

		// now test that neither bela nor panni can send request to each other any longer!
		bela->sendRequestTo(panniid);
		panni->sendRequestTo(belaid);
		printState();// good

		std::cout << "Let's say " << fanni->name << " now tags " << panni->name << std::endl;
		fanni->tagFriend(panniid);

		std::cout << "Let's say " << panni->name << " now purges stale relationships" << std::endl;
		panni->purgeStaleRelationships(); // should remove Bela

		printState();
	}

	std::cin.get();
    return 0;
}

