#pragma once

#include "computers.h"
#include <vector>

class Backlog {
public:
	Backlog() {}
	void registerDevice(Szamitogep* szp) {
		backloggedDevices.push_back(szp);
	}
	void printDevices() {
		for (Szamitogep* szp : backloggedDevices) {
			std::cout << "  In backlog: device w/ sn ";
			std::cout << szp->getSerial();
			std::cout << std::endl;
		}
	}
	void fixAllLaptops() {
		for (Szamitogep* szp : backloggedDevices) {
			Laptop* lp = dynamic_cast<Laptop*>(szp);
			if (lp) {
				lp->receiveFromSzerviz();
			}
		}

		for (auto it = backloggedDevices.begin();
			it != backloggedDevices.end();
			it++) {
				Laptop* lp = dynamic_cast<Laptop*>(*it);
				if (lp) {
					backloggedDevices.erase(it);
					break;
				}
		}
	}
private:
	std::vector<Szamitogep*> backloggedDevices;
};