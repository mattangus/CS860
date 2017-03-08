#include "firstMorph.h"

firstMorph::firstMorph()
{
	alphabetMin = 1;
	alphabetMax = 5;
	alphabetShift = 1;
	expandFactor = 2;

	vector<int> one;
	one.push_back(1);
	one.push_back(2);

	vector<int> two;
	two.push_back(2);
	two.push_back(3);

	vector<int> three;
	three.push_back(1);
	three.push_back(4);

	vector<int> four;
	four.push_back(3);
	four.push_back(2);

	values.push_back(one);
	values.push_back(two);
	values.push_back(three);
	values.push_back(four);
}

firstMorph::~firstMorph()
{

}
