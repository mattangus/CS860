#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

template <typename T>
class matrix {
private:
	vector<T> data_vec;
public:
	size_t rows;
	size_t cols;
	matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data_vec(rows*cols)
	{
		if(rows != cols)
			throw std::runtime_error("rows != cols, only square supported");
		if(rows <= 0 || cols <= 0)
			throw runtime_error("must have positive dimensions");
	}

	matrix(const matrix &other) : rows(other.rows), cols(other.cols), data_vec(other.data_vec)
	{
	}

	~matrix()
	{
	}

	T& operator ()( size_t row, size_t col ) {
		if (row > rows || col > cols) throw std::out_of_range("matrix");
		return data_vec[ row * cols + col ];
	}

	void swap(matrix<T> &other)
	{
		std::swap(rows,other.rows);
		std::swap(cols,other.cols);
		std::swap(data_vec,other.data_vec);
	}
	
	T det()
	{
		matrix<T> A(*this);
		matrix<T> B(A.rows,A.cols);
		condense(A,B);
		matrix<T> C(A.rows,A.cols);
		matrix<T> temp(A.rows,A.cols);
		while(A.rows >= 3)
		{
			condense(B,C);
			//divide
			for(int i = 0; i < C.rows; i++)
			{
				for(int j = 0; j < C.cols; j++)
				{
					if(A(i+1,j+1) == 0)
						cout << "divide by zero " << this->rows << ":" << A.rows << endl;
					C(i,j) /= A(i+1,j+1);
				}
			}
			temp.swap(A);
			A.swap(B);
			B.swap(C);
			C.swap(temp);
		}
		return C(0,0);
	}

	void condense(matrix<T> &A, matrix<T> &B)
	{
		B.rows = A.rows-1;
		B.cols = A.cols-1;
		for(int i = 0; i < A.rows-1; i++)
		{
			for(int j = 0; j < A.cols-1; j++)
			{
				B(i,j) = A(i,j)*A(i+1,j+1) - A(i,j+1)*A(i+1,j);
			}
		}
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
};









