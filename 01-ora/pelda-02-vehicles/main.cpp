// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vehicles.h"
#include "vehiclepark.h"
#include <iostream>

int main()
{
	// Vehicle v;
	// absztrakt osztaly, nem megy!!

	Vehicle* c1 = new Car("Oliver's Ferrari");
	Vehicle* c2 = new Car("Erno's Porsche");
	Vehicle* c3 = new Car("Adam's Mercedes");
	Vehicle* mb1 = new MotorBike("Mate's Harley");

	//c1->addPart(new Part("Air conditioner", 2));
	//c2->addPart(new Part("Engine", 6));
	//c3->addPart(new Part("Piston", 7));
	//c3->addPart(new Part("Spark plug", 3));

	VehiclePark vehiclepark;
	vehiclepark.addVehicle(c1);
	vehiclepark.addVehicle(c2);
	vehiclepark.addVehicle(c3);
	vehiclepark.addVehicle(mb1);

	vehiclepark.amortize();
	std::cout << "After 1 year:\n";
	vehiclepark.printVehicles();

	for (int y = 2; y < 10; ++y) {
		vehiclepark.amortize();
		std::cout << "After " << y << " years:\n";
		vehiclepark.printVehicles();
		if (y == 6) vehiclepark.repairCars();
		else if (y == 7) vehiclepark.repairBikes();
	}

	std::cin.get();
}

