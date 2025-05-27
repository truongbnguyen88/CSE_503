#include <iostream>
#include <set>

using namespace std;

int main()
{
	int i = 0;
	set<int> s;

	for (i = 0; i < 10; ++i)
	{
		s.insert(s.end(), 12 - i*2);
	} // end for

	set<int>::iterator itr;
	itr = s.begin();

	int sum = *itr;
	cout << "s is " << *itr << endl;

	for (itr = ++s.begin(); itr != s.end(); itr++)
	{
		cout << "s is " << *itr << endl;
		sum = sum + *itr;
	} // end for
	cout << "Sum is " << sum << endl;
	cout << endl;

	s.erase(2);
	itr = s.begin();
	sum = *itr;
	cout << "s is " << *itr << endl;
	for (itr = ++s.begin(); itr != s.end(); itr++)
	{
		cout << "s is " << *itr << endl;
		sum = sum + *itr;

	} // end for
	cout << "Sum is " << sum << endl;
	cout << endl;

	itr = s.find(10);
	s.erase(itr);
	itr = s.begin();
	sum = *itr;
	cout << "s is " << *itr << endl;
	for (itr = ++s.begin(); itr != s.end(); itr++)
	{
		cout << "s is " << *itr << endl;
		sum = sum + *itr;

	} // end for
	cout << "Sum is " << sum << endl;
	cout << endl;

	s.erase(s.find(-4), s.find(6));
	for (itr = s.begin(); itr != s.end(); itr++)
	{
		cout << "s is " << *itr << endl;
	} // end for
	cout << endl;

	return 0;
}
