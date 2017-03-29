#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include "zeroDet.h"

using namespace std;

template <typename T>
class hmatrix {
private:
	vector<int> data;
public:
	const size_t t;
	const size_t n;
	hmatrix(vector<int> data, int t) : t(t), n(data.size()), data(data)
	{
		//if(n != t*2 - 1)
		//	throw std::runtime_error("n != t*2 - 1, only square supported");
	}

	~hmatrix()
	{
	}

	#define IDX(i,j) ((i)*(n) + (j))
	T det()
	{
		vector<T> dets((t+1)*data.size());

		//base case
		for(int i = 0; i < data.size(); i++)
		{
			dets[IDX(0,i)] = 1;
			dets[IDX(1,i)] = data[i];
		}

		int stopPoint = data.size() - 2;
		for(int i = 2; i < t+1; i++)
		{
			//#pragma omp parallel for
			for(int j = 0; j < stopPoint; j++)
			{
				dets[IDX(i,j)] = (dets[IDX(i-1,j)]*dets[IDX(i-1,j+2)] - dets[IDX(i-1,j+1)]*dets[IDX(i-1,j+1)])/dets[IDX(i-2,j+2)];
				if(dets[IDX(i,j)] == 0)
					throw zeroDet("zero det found i=" + to_string(i) + " j=" + to_string(j));
			}
			stopPoint -= 2;
			//cout << endl;
		}

		return dets[IDX(t,0)];
	}

	void checkDets()
	{
		//cout << endl << endl;
		//only keep needed rows
		vector<T> minus1(data.size());
		vector<T> minus2(data.size());

		//base case
		for(int i = 0; i < data.size(); i++)
		{
			minus2[i] = 1;
			minus1[i] = data[i];
			//cout << minus1[i] << "\t";
		}
		//cout << endl;

		int stopPoint = data.size() - 2;
		for(int i = 2; i < t+1; i++)
		{
			vector<T> minus0(stopPoint);
			
			for(int j = 0; j < stopPoint; j++)
			{
				minus0[j] = (minus1[j]*minus1[j+2] - minus1[j+1]*minus1[j+1])/minus2[j+2];
				//cout << minus0[j] << "\t";
				if(minus0[j] == 0)
					throw zeroDet("zero det found i=" + to_string(i) + " j=" + to_string(j));
			}
			minus2.swap(minus1);
			minus1.swap(minus0);
			stopPoint -= 2;
			//cout << endl;
		}
	}
};









