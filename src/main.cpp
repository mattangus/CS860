#include <iostream>
#include <time.h>
#include <iomanip>
#include <boost/rational.hpp>
#include <chrono>
#include "matrix.h"
#include "firstMorph.h"
#include "sequence.h"
#include <map>

using namespace std;

typedef boost::rational<int> rational;

void addUnique(vector<int> &sub, vector<vector<int> > &list);
void print(map<vector<int>, bool> &list);

int main()
{
	firstMorph f;
	sequence seq(f,1);
	//brute force base case
	map<vector<int>, bool> list;
	
	for(int i = 0; i < 10000; i++)
	{
		vector<int> sub;
		for(int j = 0; j < 2; j++)
			sub.push_back(seq[i+j]);
		list[sub] = true;
	}
	cout << "Base Case: ";
	print(list);
	
	//inductive step
	for(int t = 2; t < 1000; t++)
	{
		int n = 2*t-1;
		map<vector<int>, bool> expansions = f.expandAll(list);
		while(expansions.begin()->first.size() <= n)
		{
			cout << expansions.begin()->first.size() << endl;
			expansions = f.expandAll(expansions);
		}
		map<vector<int>, bool> nList;

		for(map<vector<int>, bool>::iterator it=expansions.begin(); it != expansions.end(); ++it)
		{
			vector<int> cur = it->first;
			for(int start = 0; start <= cur.size() - n; start++)
			{
				vector<int> sub;
				for(int j = 0; j < n; j++)
					sub.push_back(cur[start + j]);
				nList[sub] = true;
			}
		}
		cout << n << endl;
		list = nList;
	}

}

void print(map<vector<int>, bool> &list)
{
	cout << "{";
	for(map<vector<int>, bool>::iterator it=list.begin(); it != list.end(); ++it)
	{
		vector<int> cur = it->first;
		for(int j = 0; j < cur.size(); j++)
		{
			cout << cur[j];
		}
	}
	cout << "}" << endl;
}

void addUnique(vector<int> &sub, vector<vector<int> > &list)
{
	bool hasDup = false;
	for (int i = 0; i < list.size(); i++)
	{
		vector<int> cur = list[i];
		if (sub.size() != cur.size())
			throw runtime_error("wrong size");
		bool same = true;
		for (int j = 0; j < cur.size(); j++)
		{
			if (cur[j] != sub[j])
				same = false;
		}
		if (same)
			hasDup = true;
	}
	if (!hasDup)
		list.push_back(sub);
}
