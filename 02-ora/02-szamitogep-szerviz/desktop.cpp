#include "stdafx.h"
#include "computers.h"

Desktop::Desktop(int s) : Szamitogep(s) {
}

void Desktop::print() {
	std::cout << "I am a Desktop computer w/ SN: " << getSerial() << std::endl;
}

void Desktop::szetszerel() {
	std::cout << "A Desktop gep minden alkatresze cserelheto" << std::endl;
}