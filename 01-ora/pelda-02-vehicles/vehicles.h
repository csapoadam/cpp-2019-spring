#pragma once


#include <string>
#include <iostream>

class Vehicle {
private:
	std::string name;
	int lifetime;
	const int initialLifetime;
protected:
	int getLifetime() const { return lifetime; }
	void setLifetime(int lt) { lifetime = lt; }
public:
	Vehicle(std::string n, int ltime) : name(n), lifetime(ltime), initialLifetime(ltime) {
	}
	virtual void amortize() = 0; // pure virtual fv -> Vehicle absztrakt osztaly
	void printStatus() const {
		std::cout << name << ": " << lifetime << " years left" << std::endl;
	}
	void repair() {
		lifetime = initialLifetime;
	}
};

class Car : public Vehicle { // public öröklés! mivel Car is-a Vehicle
public:
	Car(std::string n) : Vehicle(n, 10) {}
	void amortize() {
		if (getLifetime() > 0) {
			setLifetime(getLifetime() - 1);
		}
	}

};

class MotorBike : public Vehicle { // public öröklés! mivel Car is-a Vehicle
public:
	MotorBike(std::string n) : Vehicle(n, 4) {}
	void amortize() {
		if (getLifetime() > 0) {
			setLifetime(getLifetime() - 1);
		}
	}
};
