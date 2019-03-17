#pragma once

#include <iostream>

// ez az osztaly kesobb is hozzaadhato, anelkul hogy
// a main.cpp-ben vgy plaindog.h-ban barmit valtoztatnank
// (leszamitva a main.cpp-beli include-ot)
// A lenyeg, hogy testfunction fv-t nem kell modositani RedDog miatt
class RedDog : public Dog {
public:
	RedDog() : Dog("RedDog") {}
	void print() {
		std::cout << "I am a fully red dog." << std::endl;
	}

};