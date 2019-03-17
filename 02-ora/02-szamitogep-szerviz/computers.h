#pragma once

#include <iostream>
// #include "management.h"
class Backlog;

class Szamitogep {
public:
	Szamitogep(int);
	virtual void print() = 0;
	int getSerial();
private:
	int serial;
};

class Desktop : public Szamitogep {
public:
	Desktop(int s);
	void print() override;
	void szetszerel();
};

class Laptop : public Szamitogep {
public:
	Laptop(int);
	void print() override;
	void szervizeltet(Backlog* bp);
	void receiveFromSzerviz();
private:
	bool isInSzerviz;
};