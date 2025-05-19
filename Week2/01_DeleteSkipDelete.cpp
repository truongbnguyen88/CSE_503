#include <iostream>
#include <vector>
using namespace std;

void printVector(const vector<int> &);

template<typename Container>
void removeEveryOtherItem(Container & lst)
{
	typename Container::iterator itr = lst.begin();
	while (itr != lst.end())
	{
		itr = lst.erase(itr);
		if (itr != lst.end())
			++itr;
	}
}

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
			out << ", " << *itr++;
		out << " ]" << endl;
	}
}

void printVector(const vector<int> & v)
{
	{
		if (v.empty())
		{
			cout << "(empty)";
		}
		else
		{
			vector<int>::const_iterator itr = v.begin();
			cout << "[ " << *itr++; // Print first item
			while (itr != v.end())
				cout << ", " << *itr++;

			cout << " ]" << endl;
		}
	}
}

int main()
{
	vector<int> v1(10);
	for (unsigned i = 0; i < v1.size(); i++)
	{
		v1[i] = int(2*i);
	}
	printCollection(v1, cout);
	removeEveryOtherItem(v1);
	printCollection(v1, cout);
	printVector(v1);

	return 0;
}
