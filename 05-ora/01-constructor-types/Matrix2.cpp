// Matrix2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"

void worker() {
	Matrix m1(3, 4);
	m1[2][3] = 10;
	m1.print();
}

int main()
{
	worker();
	std::cin.get();
    return 0;
}

