#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class matrix {
	vector<T> data_vec;
public:
	size_t const rows;
	size_t const cols;
	matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data_vec( rows * cols )
	{
		if(rows != cols)
			throw std::runtime_error("rows != cols");
	}
	matrix(T* data, size_t rows, size_t cols) : rows(rows), cols(cols), data_vec(data, data + sizeof(data) / sizeof(data[0]))
	{
		if(rows != cols)
			throw std::runtime_error("rows != cols");
	}
	
	T& operator ()( size_t row, size_t col ) {
		if (row > rows || col > cols) throw std::out_of_range("matrix");
		return data_vec[ row * cols + col ];
	}

	void print()
	{
		for (int i=0; i<rows; i++)
		{
			for (int j=0; j<cols; j++)
			{
				cout << setw(7) << setprecision(4) << (*this)(i,j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	void decompose(matrix<T> &L, matrix<T> &U) {
		register int i, j, k;
		T sum;

		for (i = 0; i < rows; i++) {
			U(i,i) = 1;
		}

		for (j = 0; j < rows; j++) {
			for (i = j; i < rows; i++) {
				sum = 0;
				for (k = 0; k < j; k++) {
					sum = sum + L(i,k) * U(k,j);	
				}
				L(i,j) = (*this)(i,j) - sum;
			}

			for (i = j; i < rows; i++) {
				sum = 0;
				for(k = 0; k < j; k++) {
					sum = sum + L(j,k) * U(k,i);
				}
				if (L(j,j) == 0) {
					cout << "det(L) close to 0!" << endl << "Can't divide by 0..." << endl;
					exit(EXIT_FAILURE);
				}
				U(j,i) = ((*this)(j,i) - sum) / L(j,j);
			}
		}
	}
	
	T det()
	{
		matrix<T> L(rows,cols);
		matrix<T> U(rows,cols);
		this->decompose(L,U);
		
		T prod = 1;

		for(int i = 0; i < rows; i++)
			prod *= L(i,i)*U(i,i);
		return prod;
	}
};
