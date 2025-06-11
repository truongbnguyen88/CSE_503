#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void printVector(vector<int> & h)
{
	unsigned int i;
	// cout << "[";
	// for (i = 0; i < h.size() - 1; ++i)
	// {
	// 	cout << setfill(' ') << setw(2) << i << ",";
	// } // end for
	// cout << i << "]" << endl;

	cout << "[";
	for (i = 0; i < h.size() - 1; ++i)
	{
		cout << setfill(' ') << setw(2) << h[i] << ",";
	} // end for
	cout << h[i] << "]" << endl;
}

void printVector(vector<int> & h, int start, int end)
{
	int i;
	cout << "[";
	for (i = start; i < start+end - 1; ++i)
	{
		cout <<  h[i] << ",";
	} // end for
	cout <<  h[i] << "]" << endl;
}

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template<typename Comparable>
const Comparable & median3(vector<Comparable> & a, int left, int right)
{
	int center = (left + right) / 2;
	cout << "In the median: " << a[left] << ", " << a[center] << ", " << a[right] << endl;
	if (a[center] < a[left])
		swap(a[left], a[center]);
	if (a[right] < a[left])
		swap(a[left], a[right]);
	if (a[right] < a[center])
		swap(a[center], a[right]);

	// Place pivot at position right - 1
	printVector(a);
	swap(a[center], a[right]);
	printVector(a);
	return a[right];
}

/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template<typename Comparable>
void insertionSort(vector<Comparable> & a, int left, int right)
{
	cout << "starting insertion sort" << endl;
	printVector(a, left, right - left + 1);
	for (int p = left + 1; p <= right; p++)
	{
		Comparable tmp = a[p];
		int j;

		for (j = p; j > left && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template<typename Comparable>
void quicksort(vector<Comparable> & a, int left, int right)
{
	cout << "In Quick Sort" << endl;
	printVector(a);
	if (left + 3 <= right)
	{
		Comparable pivot = median3(a, left, right);
		cout << "The Pivot is " << pivot << endl;
		// Begin partitioning
		int i = left, j = right; // -1;
		for (;;)
		{
			while (a[++i] < pivot)
			{
				cout << "In while 1" << endl;
			}
			while (pivot < a[--j])
			{
				cout << "In while 2" << endl;
			}
			if (i < j)
			{
				swap(a[i], a[j]);
				cout << "swapped " << a[i] << " with " << a[j] << endl;
				printVector(a);
			}
			else
				break;
		}
		swap(a[i], a[right]); // Restore pivot

		// printVector(a);
		quicksort(a, left, i - 1); // Sort small elements
		quicksort(a, i + 1, right); // Sort large elements
	}
	else
	{
		// Do an insertion sort on the subarray
		insertionSort(a, left, right);
	}
}


/**
 * Quicksort algorithm (driver).
 */
template<typename Comparable>
void quicksort(vector<Comparable> & a)
{
	quicksort(a, 0, a.size() - 1);
}



int main()
{
	vector<int> h(14);

	h[0] = 31;
	h[1] = 41;
	h[2] = 59;
	h[3] = 26;
	h[4] = 53;
	h[5] = 58;
	h[6] = 77;
	h[7] = 81;
	h[8] = 91;
	h[9] = 79;
	h[10] = 36;
	h[11] = 54;
	h[12] = 5;
	h[13] = 97;

	printVector(h);
	quicksort(h);
	printVector(h);
	return 0;
}
