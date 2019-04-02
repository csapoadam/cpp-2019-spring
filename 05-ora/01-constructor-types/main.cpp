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

	m1.print();
	m2.print();
}

int main()
{
	worker();
	std::cin.get();
	return 0;
}

