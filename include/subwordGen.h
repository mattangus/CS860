#pragma once
#include "morphism.h"
#include "sequence.h"
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

class subwordGen
{
	morphism morph;
	map<vector<int>, bool> baseExpansion;
	void print(map<vector<int>, bool> &list);
public:
	subwordGen(morphism morph);
	~subwordGen();
	vector<vector<int> > getSubwords(int n);
	vector<vector<int> > getBaseExpansion(int n);
	void print();
};
