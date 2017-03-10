#include <iostream>
#include <boost/multiprecision/gmp.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <map>
#include <fstream>
#include <time.h>
#include <chrono>
#include "hmatrix.h"
#include "firstMorph.h"
#include "sequence.h"
#include "subwordGen.h"
#include "zeroDet.h"

using namespace std;

typedef boost::multiprecision::mpz_int matType;
//typedef int matType;
namespace po = boost::program_options;

void logCheckpoint(int t, string file);
void testDet();
void testLarge();
void checkDets(morphism m, int t);

int main(int argc, const char** argv)
{
	//testDet();
	//testLarge();
	
	string morphFile;
	int t;
	string checkpointFile;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "print this message")
		("morphism,m", po::value<string>(&morphFile)->required(), "path to morphism file")
		("size,t", po::value<int>(&t)->required(), "size of hankel determinant to compute. subwords up to 2t-1 in length")
		("checkpoint,c", po::value<string>(&checkpointFile), "checkpoint file NOT SUPPORTED")
	;
	
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	
	if(vm.count("help"))
	{
		cout << desc << endl;
		return 0;
	}

	try {
		po::notify(vm);
	} catch (exception &ex) {
		cout << ex.what() << endl;
		return 0;
	}

	morphism m(morphFile);
	cout << "starting at t=" << t << endl;
	cout << "morphism:" << endl;
	m.print();
	cout << "checkpoint file: " << checkpointFile << endl;
	checkDets(m,t);
	cout << "done!" << endl << flush;
}

void checkDets(morphism m, int t)
{
	subwordGen sg(m,m.alphabetMin);
	cout << "starting" << endl;
	int n = 2*t-1;
	auto startSubword = chrono::high_resolution_clock::now();
	vector<vector<int> > subwords = sg.getSubwords(n);
	auto endSubword = chrono::high_resolution_clock::now();
	int genTime = chrono::duration_cast<chrono::milliseconds>(endSubword - startSubword).count();
	cout << "t=" << t;
	cout << ":\t#sub=" << subwords.size() << "\tgent=" << ((float)genTime/1000.0) << " s\t";
	cout << flush;
	auto start = chrono::high_resolution_clock::now();
	#pragma omp parallel for
	for(int i = 0; i < subwords.size(); i++)
	{
		//matrix<matType> mat = matrix<matType>::hankel(subwords[i]);
		//matType val = mat.det();
		hmatrix<matType> mat(subwords[i]);
		matType val;
		try {		
			val = mat.det();
		} catch (zeroDet ex) {
			cout << ex.what() << endl;
			cout << "found zero det: t=" << t << ",n=" << n << endl;
		}
		if(val == 0)
		{
			cout << "found zero det: t=" << t << ",n=" << n << endl;
		}
	}
	auto end = chrono::high_resolution_clock::now();
	int difMs = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	cout << ((float)difMs/1000.0) << " s" << "\t(" << (((float)difMs/1000.0)/subwords.size()) << " s avg)" << endl;
}

void testLarge()
{
	/*firstMorph f;
	sequence s(f,1);
	vector<int> data;
	for(int i = 0; i < 2*1000-1; i++)
	{
		data.push_back(s[i]);
	}
	cout << "got all data" << endl;
	hmatrix<matType> mat(data);
	cout << "starting det calc" << endl;
	auto start = chrono::high_resolution_clock::now();
	matType value = mat.det();
	auto end = chrono::high_resolution_clock::now();
	int difMs = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	cout << value << endl;
	cout << ((float)difMs/1000.0) << " s" << endl;*/
	
	/*int n = 4;
	int min = 1;
	int max = 10;
	srand(time(NULL));
	int arr[4][4] = {{1,2,2,3}, {2,2,3,1}, {2,3,1,4}, {3,1,4,2}}; //28
	//int arr[4][4] = {{-2,-1,-1,-4}, {-1,-2,-1,-6}, {-1,-1,2,4}, {2,1,-3,-8}}; //-8
	for(int nTest = 0; nTest < 1; nTest++)
	{
		hmatrix<int> mat(n,n);
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				mat(i,j) = arr[i][j];//exp((rand() % (max - min)) + min);
			}
		}
		cout << "here" << endl;
		int value = mat.det();
		cout << value << endl;
		/*matType a = mat(0,0);matType b = mat(0,1);matType c = mat(0,2);
		matType d = mat(1,0);matType e = mat(1,1);matType f = mat(1,2);
		matType g = mat(2,0);matType h = mat(2,1);matType i = mat(2,2);
		matType expected = a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
		if(value != expected)
			cout << "big trouble  " << value << "!=" << expected << endl;
	}*/
}

/*void testDet()
{
	int n = 2;
	int min = -100;
	int max = 100;
	srand(time(NULL));
	for(int nTest = 0; nTest < 200; nTest++)
	{
		matrix<matType> mat(n,n);
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				mat(i,j) = (rand() % (max - min)) + min;
			}
		}
		matType value = mat.det();
		matType expected = mat(0,0)*mat(1,1) - mat(1,0)*mat(0,1);
		if(value != expected)
			cout << "big trouble" << endl;
	}
}*/

void logCheckpoint(int t, string file)
{
	ofstream ofs(file, ios::out | ios::trunc);
	ofs << t;
	ofs.close();
}
