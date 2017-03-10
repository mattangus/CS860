#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define IDX(A,row,col) (A.data[ ((row) * A.cols) + (col) ])

template <typename T>
class matrix {
private:
	vector<T> data;
	bool isHankel = false;
public:
	size_t rows;
	size_t cols;
	matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows*cols)
	{
		if(rows != cols)
			throw std::runtime_error("rows != cols, only square supported");
		if(rows <= 0 || cols <= 0)
			throw runtime_error("must have positive dimensions");
	}

	matrix(const matrix &other) : rows(other.rows), cols(other.cols), data(other.data)
	{
	}

	~matrix()
	{
	}

	T& operator ()( size_t row, size_t col ) {
		if (row > rows || col > cols) throw std::out_of_range("matrix");
		return data[ row * cols + col ];
	}

	void swap(matrix<T> &other)
	{
		std::swap(rows,other.rows);
		std::swap(cols,other.cols);
		std::swap(data,other.data);
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
			cout << "A:" << endl;
			A.print();
			cout << "B:" << endl;
			B.print();
			//divide
			for(int i = 0; i < C.rows; i++)
			{
				for(int j = 0; j < C.cols; j++)
				{
					if(IDX(A,i+1,j+1) == 0)
						cout << "divide by zero " << this->rows << ":" << A.rows << endl;
					IDX(C,i,j) /= IDX(A,i+1,j+1);
				}
			}
			cout << "C:" << endl;
			C.print();
			temp.swap(A);
			A.swap(B);
			B.swap(C);
			C.swap(temp);
		}
		//return B because b and c were swapped
		return B(0,0);
		return 0;
	}

	void condense(matrix<T> &A, matrix<T> &B)
	{
		B.rows = A.rows-1;
		B.cols = A.cols-1;
		if(!A.isHankel)
		{
			for(int i = 0; i < B.rows; i++)
			{
				for(int j = 0; j < B.cols; j++)
				{
					IDX(B,i,j) = IDX(A,i,j)*IDX(A,i+1,j+1) - IDX(A,i,j+1)*IDX(A,i+1,j);
				}
			}
		}
		else
		{
			int lastCol = B.cols-1;
			//upper off diag
			for(int j = 0; j < B.cols; j++)
			{
				T val = IDX(A,0,j)*IDX(A,1,j+1) - IDX(A,0,j+1)*IDX(A,1,j);
				int temp = j;
				for(int i = 0; i < B.rows && temp >= 0; i++)
				{
					IDX(B,i,temp) = val;
					temp--;
				}
			}
			//lower off diag
			for(int i = 1; i < B.rows; i++)
			{
				T val = IDX(A,i,lastCol)*IDX(A,i+1,lastCol+1) - IDX(A,i,lastCol+1)*IDX(A,i+1,lastCol);
				int temp = i;
				for(int j = lastCol; j > 0 && temp < B.rows; j--)
				{
					IDX(B,temp,j) = val;
					temp++;
				}
			}
			B.isHankel = true;
		}
	}

	static matrix<T> hankel(vector<int> &list)
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
		ret.isHankel = true;
		return ret;
	}

	void print()
	{
		for (int i=0; i<rows; i++)
		{
			for (int j=0; j<cols; j++)
			{
				cout << (*this)(i,j) << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
};









