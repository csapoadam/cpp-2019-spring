#pragma once
#include <iostream>

class Matrix {
private:
	const int nrows;
	const int ncols;
	int** data;
	void unsafeCopyValuesFrom(const Matrix& other);
public:
	Matrix(int rows, int cols);
	~Matrix();
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	void print();
	int* operator[](int rowinx);
};

