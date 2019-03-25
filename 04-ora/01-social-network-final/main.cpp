// SocialNetwork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "networkmanager.h"
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

	netmgr->createRequest(belaid, panniid);
	netmgr->createRequest(belaid, panniid); // should print request already sent...
	netmgr->createRequest(belaid, belaid); // cannot send to oneself
	netmgr->createRequest(belaid, 15); // no such user w/ id of 15
	
	netmgr->createRequest(fanniid, panniid);

	printState();

	//std::cout << "Panni now accepts request from Bela" << std::endl;
	//netmgr->acceptRequest(panniid, belaid);
	std::cout << "Panni will now accept all requests" << std::endl;
	netmgr->acceptAllRequests(panniid);
	std::cout << std::endl;
	std::cout << "so we now have:" << std::endl;
	printState();

	// now test that neither bela nor panni can send request to each other any longer!
	netmgr->createRequest(belaid, panniid);
	netmgr->createRequest(panniid, belaid);
	printState();// good

	std::cout << "Let's say Fanni now tags Panni" << std::endl;
	netmgr->tag(fanniid, panniid);

	std::cout << "Let's say Panni now purges stale relationships" << std::endl;
	netmgr->purgeStaleRelationships(panniid); // should remove Bela

	printState();

	std::cin.get();
    return 0;
}

