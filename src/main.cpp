#include <iostream>
#include <boost/rational.hpp>
#include <string>
#include <map>
#include <fstream>
#include <time.h>
#include <chrono>
#include "matrix.h"
#include "firstMorph.h"
#include "sequence.h"
#include "argparse.h"
#include "subwordGen.h"

using namespace std;

typedef boost::rational<int> rational;

void logCheckpoint(int t, string file);
void testDet();

int main(int argc, const char** argv)
{
	//testDet();
	
	ArgumentParser parser;

	parser.addArgument("-m",1);
	parser.addArgument("-c",1);

	parser.parse(argc,argv);

	//todo replace with parsed args. keep getting bad cast exception
	morphism m;
	int morph = 1;
	if(morph == 1)
		m = firstMorph();
	else if(morph == 2)
	{
		//todo: add second morphism
		cout << "not implemented" << endl;
		return 1;
	}
	
	string checkpoint = "checkpoint.txt";
	
	ifstream ifs(checkpoint);
	int startT = 2;
	if(ifs.good())
	{
		ifs >> startT;
		startT++;
		cout << "starting from " << startT << endl;
	}
	ifs.close();

	subwordGen sg(m,m.alphabetMin);

	for(int t = startT; t < 1000; t++)
	{
		int n = 2*t-1;
		auto startSubword = chrono::high_resolution_clock::now();
		vector<vector<int> > subwords = sg.getSubwords(n);
		auto endSubword = chrono::high_resolution_clock::now();
		auto start = chrono::high_resolution_clock::now();
		#pragma omp parallel for
		for(int i = 0; i < subwords.size(); i++)
		{
			matrix<rational> mat = matrix<rational>::hankel(subwords[i]);
			rational val = mat.det();
			if(val == 0)
			{
				cout << "found zero det: t=" << t << ",n=" << n << endl;
			}
		}
		auto end = chrono::high_resolution_clock::now();
		int difMs = chrono::duration_cast<chrono::milliseconds>(end - start).count();
		int genTime = chrono::duration_cast<chrono::milliseconds>(endSubword - startSubword).count();
		cout << "t=" << t;
		cout << ":\t#sub=" << subwords.size() << "\tgent=" << ((float)genTime/1000.0) << " s\t";
		cout << ((float)difMs/1000.0) << " s" << "\t(" << (((float)difMs/1000.0)/subwords.size()) << " s avg)" << endl;
		logCheckpoint(t,checkpoint);
	}
}

void testDet()
{
	int n = 2;
	int min = -100;
	int max = 100;
	srand(time(NULL));
	for(int nTest = 0; nTest < 200; nTest++)
	{
		matrix<rational> mat(n,n);
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				mat(i,j) = (rand() % (max - min)) + min;
			}
		}
		rational value = mat.det();
		rational expected = mat(0,0)*mat(1,1) - mat(1,0)*mat(0,1);
		if(value != expected)
			cout << "big trouble" << endl;
	}
}

void logCheckpoint(int t, string file)
{
	ofstream ofs(file, ios::out | ios::trunc);
	ofs << t;
	ofs.close();
}



