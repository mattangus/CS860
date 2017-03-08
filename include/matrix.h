#pragma once
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

template <typename T>
class matrix {
private:
	T* data_vec;
public:
	size_t const rows;
	size_t const cols;
	matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
	{
		if(rows != cols)
			throw std::runtime_error("rows != cols, only square supported");
		data_vec = new T[rows*cols];
	}

	~matrix()
	{
		delete [] data_vec;
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
				cout << (*this)(i,j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	//in place is faster
	#define IDX(i,j) (size*(i) + (j))
	T det()
	{
		//decompose in place using openmpi
		T* matrix = new T[rows*cols];
		memcpy(matrix,data_vec,sizeof(T)*rows*cols);
		int size = rows;
		/* in situ LU decomposition */
		int k;

		//LU-decomposition based on Gaussian Elimination
		// - Arranged so that the multiplier doesn't have to be computed multiple times
		for(k = 0; k < size-1; k++)
		{ //iterate over rows/columns for elimination
			int row;
			// The "multiplier" is the factor by which a row is multiplied when
			//  being subtracted from another row.
			//#pragma omp parallel for private(row) shared(matrix)
			for(row = k + 1; row < size; row++)
			{
				int col;

				// the multiplier only depends on (k,row),
				// it is invariant with respect to col
				T factor = matrix[IDX(row,k)]/matrix[IDX(k,k)];

				//Eliminate entries in sub matrix (subtract rows)
				for(col = k + 1; col < size; col++){ //column
				matrix[IDX(row,col)] = matrix[IDX(row,col)] - factor*matrix[IDX(k,col)];
			}

			matrix[IDX(row,k)] = factor;
			}
		}
		
		T prod = 1;

		for(int i = 0; i < rows; i++)
			prod *= matrix[IDX(i,i)];
		
		delete [] matrix;
		
		return prod;
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
	
	T det2()
	{
		matrix<T> L(rows,cols);
		matrix<T> U(rows,cols);
		this->decompose(L,U);
		
		T prod = 1;

		for(int i = 0; i < rows; i++)
			prod *= L(i,i)*U(i,i);
		return prod;
	}

	static matrix<T> hankel(vector<int> list)
	{
		int n = list.size();
		int t = (n+1)/2;
		if(2*t-1 != n)
			throw std::runtime_error("can't create square hankel matrix. t=" + to_string(t) + " n=" + to_string(n));
		matrix<T> ret(t,t);
		for(int i = 0; i < t; i++)
		{
			for(int j = 0; j < t; j++)
			{
				ret(i,j) = list[i+j];
			}
		}
		return ret;
	}

};









