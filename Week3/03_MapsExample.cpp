#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<string, double> salaries;

	salaries["Pat"] = 95000;
	salaries["Jan"] =105000;

	cout << salaries["Pat"] << endl;
	cout << salaries["Imam"] << endl; // notice that it creates an entry for Imam
	cout << salaries["Jan"] << endl;

	map<string, double>::const_iterator itr;
	itr = salaries.find("Jan");
	if (itr == salaries.end())
	{
		cout << "Could not find employee on payroll" << endl;
	}
	else
	{
		cout << itr->first << " " << itr->second << endl;
	} // end if else
	cout << endl;

	itr = salaries.find("Smith");
	if (itr == salaries.end())
	{
		cout << "Could not find employee on payroll" << endl;
	}
	else
	{
		cout << itr->first << " " << itr->second << endl;
	} // end if else
	cout << endl;

	for (itr = salaries.begin(); itr != salaries.end(); ++itr)
	{
		cout << itr->first << " " << itr->second << endl;
	} // end for

	return 0;
}
