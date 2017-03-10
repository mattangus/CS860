#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>

using namespace std;

class morphism
{
protected:
	vector<vector<int> > values;
	int alphabetShift;
public:
	int expandFactor;
	int alphabetMin;
	int alphabetMax;

	vector<int> expand(int term)
	{
		if (term < alphabetMin || term > alphabetMax)
			throw std::runtime_error("term not in alphabet");
		return values[term - alphabetShift];
	}
	
	vector<int> expand(vector<int> terms)
	{
		vector<int> ret;
		for(int i = 0; i < terms.size(); i++)
		{
			vector<int> temp = expand(terms[i]);
			for(int j = 0; j < temp.size(); j++)
			{
				ret.push_back(temp[j]);
			}
		}
		return ret;
	}

	vector<vector<int> > expandAll(vector<vector<int> > &list)
	{
		vector<vector<int> > ret;
		for(int i = 0; i < list.size(); i++)
		{
			ret.push_back(expand(list[i]));
		}
		return ret;
	}

	void expandAll(map<vector<int>, bool> &list)
	{
		map<vector<int>, bool> ret;
		for(map<vector<int>, bool>::iterator it=list.begin(); it != list.end(); ++it)
		{
			vector<int> expansion = expand(it->first);
			//cout << "expanded size " << it->first.size() << " to " << expansion.size() << endl;
			ret[expansion] = true;
		}
		ret.swap(list);
	}

	virtual ~morphism() { }
};
