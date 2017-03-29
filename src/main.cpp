#include <iostream>
#include <boost/multiprecision/gmp.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <map>
#include <fstream>
#include <time.h>
#include <chrono>
#include "hmatrix.h"
#include "sequence.h"
#include "subwordGen.h"
#include "zeroDet.h"
#include <omp.h>

using namespace std;

typedef boost::multiprecision::mpz_int matType;
//typedef int matType;
namespace po = boost::program_options;

void logCheckpoint(int t, string file);
void checkDets(morphism m, int t);

int main(int argc, const char** argv)
{
	string morphFile;
	int t;
	string checkpointFile;
	int threads = 0;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "print this message")
		("morphism,m", po::value<string>(&morphFile)->required(), "path to morphism file")
		("size,t", po::value<int>(&t)->required(), "size of hankel determinant to compute. subwords up to 2t-1 in length")
		("checkpoint,c", po::value<string>(&checkpointFile), "checkpoint file NOT SUPPORTED")
		("threads,h", po::value<int>(&threads), "number of threads to use (default is number of cores)")
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
	if(threads != 0)
	{
		omp_set_num_threads(threads);
	}
	cout << morphFile << endl;
	morphism m(morphFile);
	cout << "starting at t=" << t << endl;
	cout << "morphism:" << endl;
	m.print();
	cout << "checkpoint file: " << checkpointFile << endl;
	checkDets(m,t);
	cout << "done!" << endl << flush;
}

void checkDets(morphism m, int startT)
{
	subwordGen sg(m);
	cout << "starting" << endl;
	//int t = startT;
	for(int t = startT;; t*=2)
	{
		int n = 2*t-1;
		auto startSubword = chrono::high_resolution_clock::now();
		vector<vector<int> > subwords = sg.getBaseExpansion(n);
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
			hmatrix<matType> mat(subwords[i], t);
			try {
				mat.checkDets();
			} catch (zeroDet ex) {
				cout << ex.what() << endl;
				cout << "found zero det: t=" << t << ",n=" << n << endl;
			}
		}
		auto end = chrono::high_resolution_clock::now();
		int difMs = chrono::duration_cast<chrono::milliseconds>(end - start).count();
		cout << ((float)difMs/1000.0) << " s" << "\t(" << (((float)difMs/1000.0)/subwords.size()) << " s avg)" << endl;
	}

}

void logCheckpoint(int t, string file)
{
	ofstream ofs(file, ios::out | ios::trunc);
	ofs << t;
	ofs.close();
}
