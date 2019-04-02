#include "stdafx.h"
#include "matrix.h"

Matrix::Matrix(int rows, int cols) : 
	nrows(rows), ncols(cols)
{
	try {
		data = new int*[nrows];
		for (int r = 0; r < nrows; r++) {
			data[r] = new int[ncols];
			for (int c = 0; c < ncols; c++) {
				data[r][c] = 0;
			}
		}
	}
	catch (std::bad_alloc& ba) {
		std::cout << "Out of memory :(" << std::endl;
	}
}

Matrix::~Matrix() {
	std::cout << "Destructor called" << std::endl;
	for (int r = 0; r < nrows; r++) {
		delete[] data[r];
	}
	delete[] data;
}

void Matrix::print() {
	for (int r = 0; r < nrows; r++) {
		for (int c = 0; c < ncols-1; c++) {
			std::cout << data[r][c] << ", ";
		}
		std::cout << data[r][ncols - 1] << std::endl;
	}
}


