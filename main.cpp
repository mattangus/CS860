#include <iostream>
#include <time.h>
#include <iomanip>
#include <boost/rational.hpp>
#include <chrono>
#include "include/matrix.h"

using namespace std;

typedef boost::rational<int> rational;

int main()
{
	srand(time(NULL));
	const int n = 2;
	const int max = 10;
	const int min = -10;
	
	matrix<rational> A(n, n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			A(i,j) = (rand() % (max-min))-min;
		}
	}
}


