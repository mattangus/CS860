#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class morphism
{
protected:
	vector<vector<int> > values;
public:
	int expandFactor;
	int alphabetMin;
	int alphabetMax;

	morphism(string file)
	{
		ifstream ifs(file);
		if(!ifs.good())
			throw runtime_error("file not found: " + file);
		
		ifs >> alphabetMin;
		ifs >> alphabetMax;
		ifs >> expandFactor;
		int input;
		while(!ifs.eof() && (ifs >> input))
		{
			if(values.size() < input-alphabetMin+1)
				values.resize(input-alphabetMin+1);
			
			int temp;
			while((ifs.peek() != '\n') && (ifs >> temp))
				values[input-alphabetMin].push_back(temp);

			//cout << input << " -> " << flush;
			for(int i = 0; i < values[input-alphabetMin].size(); i++)
			{
				vector<int> tmp = values[input-alphabetMin];
				//cout << tmp[i] << "\t" << flush;
			}
			//cout << endl;
		}
		//cout << values.size() << endl;
	}

	vector<int> expand(int term)
	{
		if (term < alphabetMin || term > alphabetMax)
			throw std::runtime_error("term not in alphabet");
		return values[term - alphabetMin];
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

	void print()
	{
		for(int i = 0; i < values.size(); i++)
		{
			cout << (i + alphabetMin) << " -> ";
			for(int j = 0; j < values[i].size(); j++)
			{
				cout << values[i][j] << "\t";
			}
			cout << endl;
		}
	}

};
