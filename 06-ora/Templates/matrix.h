#pragma once
#include <iostream>

template <typename T>
class Matrix {
private:
	const int nrows;
	const int ncols;
	T** data;
	void unsafeCopyValuesFrom(const Matrix& other);
public:
	Matrix(int rows, int cols, T fillValue);
	~Matrix();
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);
	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other);
	void print();
	T* operator[](int rowinx);
};

