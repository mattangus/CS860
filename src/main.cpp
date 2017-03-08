#include <iostream>
#include <time.h>
#include <iomanip>
#include <boost/rational.hpp>
#include <chrono>
#include <string>
#include "matrix.h"
#include "firstMorph.h"
#include "sequence.h"
#include "argparse.h"
#include "subwordGen.h"
#include <map>

using namespace std;

typedef boost::rational<int> rational;

int main(int argc, const char** argv)
{

	ArgumentParser parser;

	parser.addArgument("-m",1);
	parser.addArgument("-c",1);

	parser.parse(argc,argv);

	firstMorph f;

	subwordGen sg(f,1);

	//inductive step
	for(int t = 2; t < 5; t++)
	{
		int n = 2*t-1;
		map<vector<int>, bool> subwords = sg.getSubwords(n);
		for(map<vector<int>, bool>::iterator it=subwords.begin(); it != subwords.end(); ++it)
		{
			matrix<rational> mat = matrix<rational>::hankel(it->first);
			rational val = mat.det();
			if(val == 0)
			{
				cout << "found zero det: t=" << t << ",n=" << n << endl;
			}
		}
	}
}


