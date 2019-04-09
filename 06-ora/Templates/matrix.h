#pragma once
#include <iostream>

template <typename T, int v>
class Matrix {
private:
	const int nrows;
	const int ncols;
	T** data;
	int intvalue;
	void unsafeCopyValuesFrom(const Matrix& other);
public:
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, T fillValue);
	~Matrix();
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);
	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other);
	void print();
	T* operator[](int rowinx);

	void timesTwo();

	template <typename T, int v>
	friend void timesThree(Matrix<T,v>& m);
};

template <typename T, int v>
void Matrix<T, v>::timesTwo() {
	for (int r = 0; r < nrows; r++) {
		for (int c = 0; c < ncols; c++) {
			data[r][c] = data[r][c] * 2; // duck typing - does T have a * binary operator?
		}
	}
}


template <>
void Matrix<std::string, 1>::timesTwo() {
	for (int r = 0; r < nrows; r++) {
		for (int c = 0; c < ncols; c++) {
			data[r][c] = data[r][c].append(data[r][c]);
		}
	}
}

// Ezt sajnos nem lehet...
// C++ templates are not limited to classes - they can also be used to define function templates.
// Although function templates can be fully specialized, they cannot be partially specialized, 
// irrespective of whether they are member function templates or non - member function templates.
// This can be beneficial to compiler writers, but affects the flexibility and granularity of
// what developers can do.
/*
template <int v>
void Matrix<std::string, v>::timesTwo() {
	for (int r = 0; r < nrows; r++) {
		for (int c = 0; c < ncols; c++) {
			data[r][c] = data[r][c].append(data[r][c]);
		}
	}
}
*/

template <typename T, int v>
void timesThree(Matrix<T, v>& m) {
	for (int r = 0; r < m.nrows; r++) {
		for (int c = 0; c < m.ncols; c++) {
			m[r][c] = m[r][c] * 3; // duck typing - does T have a * binary operator?
		}
	}
}

template <>
void timesThree(Matrix<std::string, 1>& m) {
	for (int r = 0; r < m.nrows; r++) {
		for (int c = 0; c < m.ncols; c++) {
			std::string cur(m[r][c]);
			m[r][c] = m[r][c].append(cur).append(cur);
		}
	}
}


template <typename T, int v>
Matrix<T, v>::Matrix(int rows, int cols) :
	Matrix(rows, cols, 0)
{
}

template <>
Matrix<std::string, 1>::Matrix(int rows, int cols) :
	Matrix(rows, cols, std::string())
{
}


template <typename T, int v>
Matrix<T, v>::Matrix(int rows, int cols, T fillValue) : nrows(rows), ncols(cols), intvalue(v) {
	try {
		data = new T*[nrows];
		for (int r = 0; r < nrows; r++) {
			data[r] = new T[ncols];
			for (int c = 0; c < ncols; c++) {
				data[r][c] = fillValue;
			}
		}
	}
	catch (std::bad_alloc& ba) {
		std::cout << "Out of memory :(" << std::endl;
	}
}

template <typename T, int v>
Matrix<T, v>::Matrix(const Matrix& other) :
	Matrix(other.nrows, other.ncols)
	// constructor delegation
	// csak inicializalo listaban lehet, kulonben
	// egy uj Matrix objektum jon letre a torzsben
{
	std::cout << "copy constructor called!" << std::endl;
	this->unsafeCopyValuesFrom(other);
}

template <typename T, int v>
Matrix<T, v>::Matrix(Matrix&& other) :
	Matrix(other.nrows, other.ncols) {
	std::cout << "Move constructor called" << std::endl;
	T** olddata = data;
	data = other.data;
	other.data = olddata; // mivel other destruktora meg fog
						  // hivodni, es olddata-t amugy is fel kell szabaditani
						  // ezert tok jok vagyunk!!
}

template <typename T, int v>
Matrix<T, v>& Matrix<T, v>::operator=(const Matrix& other) {
	// inicializalni mar nem kell, hiszen mar
	// inicializalva van ez az objektum
	// viszont kell dimension check!!
	std::cout << "copy assign operator called" << std::endl;
	if (nrows != other.nrows || ncols != other.ncols) {
		throw "cannot call assign op for matrices w/ different dimensions";
	}
	// unsafe, mert feltetelezzuk h a meretek ugyanazok
	// nem baj, hogy private :)
	this->unsafeCopyValuesFrom(other);
	return *this;
}

template <typename T, int v>
Matrix<T, v>& Matrix<T, v>::operator=(Matrix&& other) {
	// inicializalni mar nem kell, hiszen mar
	// inicializalva van ez az objektum
	// viszont kell dimension check!!
	std::cout << "move assign operator called" << std::endl;
	if (nrows != other.nrows || ncols != other.ncols) {
		throw "cannot call assign op for matrices w/ different dimensions";
	}
	T** olddata = data;
	data = other.data; //ennyike...
	other.data = olddata;
	return *this;
}

template <typename T, int v>
Matrix<T, v>::~Matrix() {
	std::cout << "Destructor called" << std::endl;
	for (int r = 0; r < nrows; r++) {
		delete[] data[r];
	}
	delete[] data;
}

template <typename T, int v>
void Matrix<T, v>::print() {
	std::cout << "matrix w/ intvalue " << intvalue << std::endl;
	for (int r = 0; r < nrows; r++) {
		for (int c = 0; c < ncols - 1; c++) {
			std::cout << data[r][c] << ", ";
		}
		std::cout << data[r][ncols - 1] << std::endl;
	}
	std::cout << std::endl;
}

template <typename T, int v>
T* Matrix<T, v>::operator[](int rowinx) {
	if (rowinx < nrows && rowinx > -1) {
		return data[rowinx];
	}
	return nullptr;
}

template <typename T, int v>
void Matrix<T, v>::unsafeCopyValuesFrom(const Matrix& other) {
	for (int r = 0; r < nrows; r++) {
		for (int c = 0; c < ncols; c++) {
			data[r][c] = other.data[r][c];
		}
	}
}


