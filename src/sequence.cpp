#include "sequence.h"

void sequence::expand()
{
	vector<int> newSeq;
	for (int i = 0; i < seq.size(); i++)
	{
		int cur = seq[i];
		vector<int> expansion = rule.expand(cur);
		for (int j = 0; j < expansion.size(); j++)
			newSeq.push_back(expansion[j]);
	}
	seq = newSeq;
}

sequence::sequence(morphism &rule, int start) : rule(rule)
{
	seq.push_back(start);
}

sequence::~sequence()
{
}

int sequence::operator[](size_t i)
{
	while (seq.size() <= i)
		expand();
	return seq[i];
}

ostream& operator<<(ostream& os, const sequence& seq)
{
	for (int i = 0; i < seq.seq.size(); i++)
		os << seq.seq[i];
	return os;
}

