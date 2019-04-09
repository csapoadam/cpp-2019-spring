#include "stdafx.h"
#include "matrix.h"

template <typename T>
Matrix::Matrix(int rows, int cols, T fillValue) : 
	nrows(rows), ncols(cols)
{
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

template <typename T>
Matrix::Matrix(const Matrix& other) :
	Matrix(other.nrows, other.ncols)
	// constructor delegation
	// csak inicializalo listaban lehet, kulonben
	// egy uj Matrix objektum jon letre a torzsben
{
	std::cout << "copy constructor called!" << std::endl;
	this->unsafeCopyValuesFrom(other);
}

template <typename T>
Matrix::Matrix(Matrix&& other) :
	Matrix(other.nrows, other.ncols) {
	std::cout << "Move constructor called" << std::endl;
	T** olddata = data;
	data = other.data;
	other.data = olddata; // mivel other destruktora meg fog
						  // hivodni, es olddata-t amugy is fel kell szabaditani
						  // ezert tok jok vagyunk!!
}

template <typename T>
Matrix& Matrix::operator=(const Matrix& other) {
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

template <typename T>
Matrix& Matrix::operator=(Matrix&& other) {
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

template <typename T>
Matrix::~Matrix() {
	std::cout << "Destructor called" << std::endl;
	for (int r = 0; r < nrows; r++) {
		delete[] data[r];
	}
	delete[] data;
}

template <typename T>
void Matrix::print() {
	for (int r = 0; r < nrows; r++) {
		for (int c = 0; c < ncols-1; c++) {
			std::cout << data[r][c] << ", ";
		}
		std::cout << data[r][ncols - 1] << std::endl;
	}
	std::cout << std::endl;
}

template <typename T>
int* Matrix::operator[](int rowinx) {
	if (rowinx < nrows && rowinx > -1) {
		return data[rowinx];
	}
	return nullptr;
}

template <typename T>
void Matrix::unsafeCopyValuesFrom(const Matrix& other) {
	for (int r = 0; r < nrows; r++) {
		for (int c = 0; c < ncols; c++) {
			data[r][c] = other.data[r][c];
		}
	}
}


