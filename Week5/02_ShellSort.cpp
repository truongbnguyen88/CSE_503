#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

template<typename Comparable>
void printArray(vector<Comparable> & a)
{
	int i = 0;
	int length = a.size();

	if (length == 0)
	{
		cout << "[empty]";
	}
	else
	{
		cout << "[ ";
		while (i < length)
		{
			cout << setw(2);
			cout << a[i];
			i++;
			if (i < length)
			{
				cout << ", ";
			} // end if
		}
		cout << " ]" << endl;
	}
}

void printIndex(int in)
{
	int i = 0;
	int length = in;

	if (length == 0)
	{
		cout << "[empty]";
	}
	else
	{
		cout << "[ ";
		while (i < length)
		{
			cout << setw(2);
			cout << i;
			i++;
			if (i < length)
			{
				cout << ", ";
			} // end if
		}
		cout << " ]" << endl;
	}
}

/**
 * Shell sort, using Shell's (poor) increments.
 */
template<typename Comparable>
void shellSort(vector<Comparable> & a)
{
	for (int gap = a.size() / 2; gap > 0; gap /= 2)
	{
		cout << "Gap = " << gap << endl;
		// The following loop starts at gap 
		// and increment forward
		// Until we reach the end
		printArray(a);

		for (unsigned i = gap; i < a.size(); i++)
		{	
			cout << "Starting at a[" << i << "] = " << a[i] << endl;
			Comparable tmp = a[i];
			unsigned switches = 0;
			int j = i;

			// The loop below is a clever way of starting at a[gap] 
			// and comparing it with it's predecessors that are 
			// gap apart and doing insert sort when needed

			for (; j >= gap && tmp < a[j - gap]; j -= gap)
			{
				cout << "Switching  a[" << j << "] = " << a[j] << 
						" with a[" << j - gap << "] = " << a[j - gap] << endl;
				a[j] = a[j - gap];
				switches++;
			}
			a[j] = tmp;
			printArray(a);
			cout << "Switches = " << switches << endl;
		}
		cout << "__________________" << endl;
	}
}

void initializeV(vector<int> & V)
{
	V[0] = 81;
	V[1] = 94;
	V[2] = 11;
	V[3] = 96;
	V[4] = 12;
	V[5] = 35;
	V[6] = 17;
	V[7] = 95;
	V[8] = 28;
	V[9] = 58;
	V[10] = 41;
	V[11] = 75;
	V[12] = 15;
}

void initializeV1(vector<int> & V1)
{
	V1[0] = 34;
	V1[1] = 8;
	V1[2] = 64;
	V1[3] = 51;
	V1[4] = 32;
	V1[5] = 21;

}

int main()
{
	vector<int> V1(6);
	// vector<int> V2(13);

	initializeV1(V1);
	printArray(V1);
	cout << "Shell is starting" << endl;
	shellSort(V1);
	cout << "Shell is done" << endl;
	printArray(V1);
	
	// initializeV(V2);
	// printArray(V2);
	// cout << "Shell is starting" << endl;
	// shellSort(V2);
	// cout << "Shell is done" << endl;
	// printArray(V2);
	// cout << endl << endl;
	


	return 0;
}
