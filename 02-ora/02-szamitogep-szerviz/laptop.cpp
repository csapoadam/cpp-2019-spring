#include "stdafx.h"
#include "computers.h"
#include "management.h"

Laptop::Laptop(int sn) : Szamitogep(sn), isInSzerviz(false) {

}

void Laptop::print() {
	std::cout << "I am a Laptop computer w/ SN: ";
	std::cout << getSerial();
	if (isInSzerviz) {
		std::cout << ". I am in the szerviz :(";
	}
	std::cout << std::endl;
	
}

void Laptop::szervizeltet(Backlog* bp) {
	isInSzerviz = true;
	bp->registerDevice(this);
}

void Laptop::receiveFromSzerviz() {
	isInSzerviz = false;
}