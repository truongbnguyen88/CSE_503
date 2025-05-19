#include <iostream>
#include <list>
#include <iterator>
#include <sstream>

using namespace std;

template<typename Container>
void printCollection(const Container & c, ostream & out = cout)
{
	if (c.empty())
		out << "(empty)";
	else
	{
		typename Container::const_iterator itr = c.begin();
		out << "[ " << *itr++; // Print first item
		while (itr != c.end())
		{
			out << ", " << *itr++;
		} // end while
		out << " ]" << endl;
	}
}

template<typename Object>
void printLots(list<Object> L, list<int> P)
{
	typename list<int>::const_iterator pIter;
	typename list<Object>::const_iterator lIter;

	int i = 0;
	int pPosition = 0;

	for (pIter = P.begin(); pIter != P.end() && lIter != L.end(); ++pIter)
	{
		pPosition = *pIter;
		lIter = L.begin();
		for (i = 0; i < pPosition; ++i)
		{
			lIter++;
		}
		if (lIter != L.end())
		{
			cout << *lIter << endl;
		}
	}
}

int main()
{
	unsigned int i = 0;
	list<int> P;
	list<string> L;

	for (i = 0; i < 8; ++i)
	{
		if (i % 2 != 0)
		{
			P.push_back(i+1);
		}

		std::string s;
		std::stringstream out;
		out << i;
		s = out.str();
		L.push_back("String " + s);
	}
	printCollection(L, cout);
	printCollection(P, cout);
	printLots(L, P);
	return 0;
}
