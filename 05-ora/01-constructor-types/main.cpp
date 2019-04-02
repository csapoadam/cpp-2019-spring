// Matrix2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"

void worker() {
	Matrix m1(3, 4);
	m1[2][3] = 10;

	Matrix m2 = m1;
	// ha nem definialunk copy constructort, a fordito
	// megteszi maga!!
	// ha letiltjuk a copy constr-t, le se fordul!
	m2[2][3] = 9; // ez mindket matrixot irja!

	m1.print();
	m2.print();
	// std::cin.get();
	// 2x hivunk delete-et
	// ugyanazokra a tombokre!!
}

int main()
{
	worker();
	std::cin.get();
    return 0;
}

