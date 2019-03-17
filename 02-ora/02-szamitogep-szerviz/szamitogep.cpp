#include "stdafx.h"
#include "computers.h"

Szamitogep::Szamitogep(int i) : serial(i) {
}

int Szamitogep::getSerial() {
	return serial;
}

