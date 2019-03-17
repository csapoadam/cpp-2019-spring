#pragma once

#include <string>
#include <iostream>

class Dog {
public:
	Dog(std::string s) : name(s) {}
	// mi tortenik, ha nem virtual?
	virtual void print() {
		std::cout << name << std::endl;
	}
	std::string getName() {
		return name;
	}
private:
	std::string name;
};