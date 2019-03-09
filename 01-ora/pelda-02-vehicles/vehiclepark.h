#pragma once

#include <vector>
#include "vehicles.h"

class VehiclePark {
private:
	std::vector<Vehicle*> vehicles;
public:
	VehiclePark() {}
	void addVehicle(Vehicle* vp) {
		vehicles.push_back(vp);
	}

	void amortize() {
		for (Vehicle* vp : vehicles) {
			vp->amortize();
		}
	}

	void printVehicles() {
		for (Vehicle* vp : vehicles) {
			vp->printStatus();
		}
	}

	void repairCars() {
		for (Vehicle* vp : vehicles) {
			if (dynamic_cast<Car*>(vp)) {
				vp->repair();
			}
		}
	}

	void repairBikes() {
		for (Vehicle* vp : vehicles) {
			if (dynamic_cast<MotorBike*>(vp)) {
				vp->repair();
			}
		}
	}
};
