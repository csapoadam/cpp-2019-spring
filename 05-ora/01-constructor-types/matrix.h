#pragma once
#include <iostream>

class Matrix {
private:
	const int nrows;
	const int ncols;
	int** data;
public:
	Matrix(int rows, int cols);
	~Matrix();
	void print();
	int* operator[](int rowinx);
};

