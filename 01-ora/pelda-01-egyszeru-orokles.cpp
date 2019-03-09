// OraiPelda-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>

class Kurzus {
private:
	int letszam;
	std::string nev;
	std::vector <std::string> hallgatok;
public:
	Kurzus(std::string knev) : letszam(0), nev(knev) {
	}
	void addHallgato(std::string);
	std::string getName() const { return nev; }
	virtual void print() {
		std::cout << "A kurzus neve: " << nev << std::endl;
		std::cout << "A kurzus letszama: " << letszam << std::endl;
		std::cout << "A hallgatok nevei: " << std::endl;
		for (std::vector<std::string>::iterator it = hallgatok.begin(); it != hallgatok.end(); it++) {
			std::cout << ".. " << *(it) << std::endl;
		}
	}
};

class CppKurzus : public Kurzus {
private:
	std::string gepterem;
public:
	CppKurzus(std::string terem) : Kurzus("CppCourse"), gepterem(terem) {
	}
	void print() override {
		//std::cout << "valami hulyeseg" << std::endl;
		std::cout << "Cpp Kurzus! Neve: " << getName();
	}
};


void Kurzus::addHallgato(std::string h) {
	hallgatok.push_back(h);
	letszam++;
}

int main()
{
	std::vector<Kurzus*> courses;

	Kurzus mycourse1("Statisztika alapjai");
	Kurzus mycourse2("Algoritmuselmelet");
	mycourse2.addHallgato("Bela");
	CppKurzus mykurzus("D104");
	mykurzus.addHallgato("Ica");

	courses.push_back(&mycourse1);
	courses.push_back(&mycourse2);
	courses.push_back(&mykurzus);

	for (Kurzus* kp : courses) {
		CppKurzus* cppkp = dynamic_cast<CppKurzus*>(kp);
		if (cppkp) {
			cppkp->print();
		}
		else {
			kp->print();
		}
		//kp->print();
	}


	/*
	mykurzus.addHallgato("Pisti");
	mykurzus.addHallgato("Anna");
	mykurzus.print();
	*/
	char c;
	std::cin >> c;
    return 0;
}

