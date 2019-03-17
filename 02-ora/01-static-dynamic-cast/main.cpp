// StaticDynamicCast.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "plaindog.h"
#include "extradogs.h"

class YellowDog : public Dog {
public:
	YellowDog(std::string s) : Dog(s) {
		assignSerialNumber();
	}
	YellowDog(Dog d) : Dog(d.getName()) { //statikus konverzio ok
		assignSerialNumber();
	}
	// mi tortenik, ha print nem virtualis fv?
	void print() override {
		std::cout << "yellow: " << getName() << std::endl;
	}
	void barkYellow() {
		std::cout << serialNum << ": shall I bark or yell oh?" << std::endl;
	}
private:
	int serialNum;
	static int currentSerialNum;
	void assignSerialNumber() {
		serialNum = currentSerialNum;
		currentSerialNum++;
	}
};

int YellowDog::currentSerialNum = 0;

void testFunction(Dog* d, Dog& rd) {
	d->print();
	rd.print();

	YellowDog* yd1 = dynamic_cast<YellowDog*>(d);
	if (yd1) {
		std::cout << "first argument was a yellow dog" << std::endl;
	}
	else {
		std::cout << "first argument is just a plain ole' dog" << std::endl;
	}

	bool sentinel = false;
	try {
		YellowDog& yd2 = dynamic_cast<YellowDog&>(rd);
	}
	catch (std::bad_cast e) {
		std::cout << "second argument cannot possible be a YellowDog reference!" << std::endl;
		sentinel = true;
	}

	if (!sentinel) {
		std::cout << "second argument is a reference to an actual YellowDog" << std::endl;
	}

	// mindig mukodik
	YellowDog* yd3 = static_cast<YellowDog*>(d);
	YellowDog& yd4 = static_cast<YellowDog&>(rd);
	std::cout << "static cast dog ptr and ref to yellow dog ptr and ref" << std::endl;
	//bajban leszunk, ha d nem volt yellowDog!
	yd3->barkYellow();

	// csak akkor mukodik, ha a konverzio definialt
	YellowDog yd5 = static_cast<YellowDog>(*d);
	std::cout << "static cast dog to yellow dog" << std::endl;
}

int main()
{
	Dog d1("simakutya");
	Dog d2("simakutya2");
	YellowDog d3("sargakutya");
	YellowDog d4("sargakutya2");
	Dog d5("simakutya3");
	YellowDog d6("sargakutya3");
	RedDog d7;
	//testFunction(&d4, d6);
	testFunction(&d7, d3);
	std::cin.get();
    return 0;
}

