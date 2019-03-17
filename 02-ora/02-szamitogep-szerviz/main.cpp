// SzamitogepSzerviz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// "Szamitogep" - absztrakt ososztaly
// "Desktop" (szetszereles)
// "Laptop" (szervizbeKuld)
// Backlog
// "Periferiak" (egyelore hagyjuk)

#include "computers.h"
#include "management.h"

int main()
{
	// Szamitogep mycomp(0); // mivel absztrakt, nem peldanyosithato
	Desktop mydesktop(1);
	Laptop mylaptop(25);
	Backlog ourbacklog;
	

	// mycomp.print();
	mydesktop.print();
	mylaptop.print();

	mylaptop.szervizeltet(&ourbacklog);
	mylaptop.print();
	ourbacklog.registerDevice(&mydesktop);
	ourbacklog.printDevices();
	ourbacklog.fixAllLaptops();
	mylaptop.print();
	ourbacklog.printDevices();

	std::cin.get();
    return 0;
}
