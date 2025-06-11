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
			cout << setw(4);
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

template<typename Comparable>
void myInsertionSort(vector<Comparable> & a)
{
	// p is the pass number
	// switches is a counter for number of switches
	// in a given pass, It is not needed for the sort

	unsigned p, j, switches = 0;
	Comparable tmp;

	for (p = 1; p < a.size(); p++) // Runs (n-1) times
	{
		cout << "Starting Pass = " << p << endl ;
		printArray(a);
		cout << "Standing at a[" << p << "] = " << a[p] << " and comparing left" << endl;
		switches = 0;
		tmp = a[p];
		j = p;
		while (j > 0 && a[j - 1] > tmp) // Max comparisons or switches is p
		{
			cout << "a[" << j - 1 << "] = " << a[j - 1] << endl;
			a[j] = a[j - 1];
			j--;
			switches++;
		} // end while
		a[j] = tmp;
		// Print array and switches after every pass
		cout << "After Pass = " << p << " and " << switches 
			<< " switches the array becomes: ";
		printArray(a);
		cout << "__________________" << endl;
	}
}

template<typename Comparable>
void insertionSort(vector<Comparable> & a)
{
	unsigned p, j;
	for (p = 1; p < a.size(); p++)
	{
		Comparable tmp = a[p];
		for (j = p; j > 0 && tmp < a[j - 1]; j--)
		{
			a[j] = a[j - 1];
		} // end for
		a[j] = tmp;
	}
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

void initializeV2(vector<int> & V2)
{
	V2[0] = 8;
	V2[1] = 6;
	V2[2] = 14;
	V2[3] = 3;
	V2[4] = 32;
	V2[5] = 27;
	V2[6] = 17;
	V2[7] = 95;
	V2[8] = 28;
	V2[9] = 58;
	V2[10] = 41;
	V2[11] = 75;
	V2[12] = 15;
}

int main()
{
	vector<int> V1(6);
	vector<int> V2(12);

	initializeV1(V1);
	initializeV2(V2);

	printArray(V1);
	cout << "Insertion is starting" << endl;
	myInsertionSort(V1);
	cout << "Insertion is done" << endl;
	printArray(V1);

	printArray(V2);
	insertionSort(V2);
	printArray(V2);
	return 0;
}
