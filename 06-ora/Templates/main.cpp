// Matrix2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"
#include <string>

Matrix<int> createMatrixWOnes(int nrows, int ncols) {
	std::cout << "creating matrix w/ ones" << std::endl;
	Matrix<int> m = Matrix<int>(nrows, ncols, 1);
	std::cout << "returning new matrix" << std::endl;
	return m;
}

Matrix<int> createMatrixWTwos(int nrows, int ncols) {
	std::cout << "creating matrix w/ twos" << std::endl;
	Matrix<int> m = Matrix<int>(nrows, ncols, 2);
	std::cout << "returning new matrix" << std::endl;
	return m;
}

void worker() {
	Matrix<int> m1(3, 4, 0);
	m1[2][3] = 10;
	std::cout << "m1 created" << std::endl;

	//Matrix m2 = m1;
	Matrix<int> m2(m1); // ugyanazt jelenti
	m2[2][3] = 9; // ez mindket matrixot irja!
	std::cout << "m2 created" << std::endl;

	Matrix<int> m3(3, 4, 0);
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
	Matrix<int> m4(std::move(m3)); // azt allitjuk, hogy m3-ra
							  // mar nem lesz szukseg - hibas felhasznalas! (t.keppen)
	m4[2][3] = 7;
	std::cout << "m4 created" << std::endl;

	// ha teheti, szinten move konstruktort hasznal
	// ha nincs olyan, megteszi a copy is...
	Matrix<int> m5(createMatrixWOnes(3, 4));
	// destruktor is meghivodik, mivel eloszor kimasolja a fv-bol
	// az eredmenyt es utana megszunteti
	m5[2][3] = 6;
	std::cout << "m5 created" << std::endl;
	m5.print();
	m5 = createMatrixWTwos(3, 4);
	m5[2][3] = 6;
	std::cout << "m5 redesigned" << std::endl;

	m1.print();
	m2.print();
	m3.print(); // m3 itt most mar csupa 0 (vagy felul lett irva szemettel)
	m4.print();
	m5.print();

	Matrix<int> m6(3,3,5);
	m6.print();
	m6.timesTwo();
	m6.print();

	Matrix<char> m7(3, 3, 'a');
	m7.print();
	m7.timesTwo();
	m7.print();
	timesThree(m7);
	m7.print();

	Matrix<std::string> m8(3, 3, "a");
	m8.print();
	m8.timesTwo();
	m8.print();
	timesThree(m8);
	m8.print();
}

int main()
{
	worker();
	std::cin.get();
	return 0;
}

