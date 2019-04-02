// Matrix2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"

void worker() {
	Matrix m1(3, 4);
	m1[2][3] = 10;
	std::cout << "m1 created" << std::endl;

	//Matrix m2 = m1;
	Matrix m2(m1); // ugyanazt jelenti
	m2[2][3] = 9; // ez mindket matrixot irja!
	std::cout << "m2 created" << std::endl;

	Matrix m3(3, 4);
	m3 = m2; // m3 itt egy mar letezo objektum
			 // ezert: nem konstrukcio, hanem ertekadas
			 // muszaj: assignment operator!
			 // mas mint ez:
			 // Matrix m4 = m2; // itt a copy constr hivodik meg!
	m3[2][3] = 8;
	std::cout << "m3 created" << std::endl;
	m3.print();
	
	// move konstruktor kikenyszeritheto explicit std::move-val (ha letezik move konstr)
	// ha nem definialtuk a move konstr-t, ugyanugy copy constr fog meghivodni
	Matrix m4(std::move(m3)); // azt allitjuk, hogy m3-ra
							  // mar nem lesz szukseg - hibas felhasznalas! (t.keppen)
	m4[2][3] = 7;
	std::cout << "m4 created" << std::endl;

	m1.print();
	m2.print();
	m3.print();
	m4.print();
}

int main()
{
	worker();
	std::cin.get();
	return 0;
}
