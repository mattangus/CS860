#include "subwordGen.h"

subwordGen::subwordGen(morphism morph, int start) : morph(morph)
{
	sequence seq(morph,start);
	//brute force base case for subwords length 2
	for(int i = 0; i < (int)pow(morph.expandFactor,13); i++)
	{
		vector<int> sub;
		for(int j = 0; j < 2; j++)
			sub.push_back(seq[i+j]);
		curExpansion[sub] = true;
	}
}

subwordGen::~subwordGen()
{
	
}

vector<vector<int> > subwordGen::getSubwords(int n)
{
	map<vector<int>, bool> expansions = curExpansion;
	while(expansions.begin()->first.size() <= n)
	{
		expansions = morph.expandAll(expansions);
	}

	map<vector<int>, bool> nextExpansion;

	for(map<vector<int>, bool>::iterator it=expansions.begin(); it != expansions.end(); ++it)
	{
		vector<int> cur = it->first;
		for(int start = 0; start <= cur.size() - n; start++)
		{
			vector<int> sub;
			for(int j = 0; j < n; j++)
				sub.push_back(cur[start + j]);
			nextExpansion[sub] = true;
		}
	}
	curExpansion = nextExpansion;
	vector<vector<int> > ret;
	ret.reserve(curExpansion.size());
	for(map<vector<int>, bool>::iterator it=curExpansion.begin(); it != curExpansion.end(); ++it)
		ret.push_back(it->first);
	return ret;
}

void subwordGen::print(map<vector<int>, bool> &list)
{
	cout << "{";
	for(map<vector<int>, bool>::iterator it=list.begin(); it != list.end(); ++it)
	{
		vector<int> cur = it->first;
		for(int j = 0; j < cur.size(); j++)
		{
			cout << cur[j];
		}
		cout << ",";
	}
	cout << "}" << endl;
}

void subwordGen::print()
{
	print(curExpansion);
}
