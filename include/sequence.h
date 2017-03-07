#pragma once

#include "morphism.h"
#include <iostream>

class sequence
{
private:
	morphism &rule;
	vector<int> seq;
	void expand();
public:
	sequence(morphism &rule, int start);
	~sequence();
	int operator[](size_t i);
	friend ostream& operator<<(ostream& os, const sequence& dt);
};

