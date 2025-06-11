#include <iostream>
#include <vector>

using namespace std;

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
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template<typename Comparable>
void merge(vector<Comparable> & a, vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd)
{
	int start = leftPos;
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	// Main loop
	cout << "Starting Merge " << leftPos << ", " <<  rightEnd << endl;
	printVector(a,start, numElements);
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (a[leftPos] <= a[rightPos])
		{
			tmpArray[tmpPos++] = a[leftPos++];
		}
		else
		{
			tmpArray[tmpPos++] = a[rightPos++];
		} // end ifelse
	} // end while

	while (leftPos <= leftEnd) // Copy rest of first half
	{
		tmpArray[tmpPos++] = a[leftPos++];
	} // end while

	while (rightPos <= rightEnd) // Copy rest of right half
	{
		tmpArray[tmpPos++] = a[rightPos++];
	} // end while

	// Copy tmpArray back
	for (int i = 0; i < numElements; i++, rightEnd--)
	{
		a[rightEnd] = tmpArray[rightEnd];
	} // end for
	printVector(a,start, numElements);
	cout << "Ended Merge" << endl;
}
/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template<typename Comparable>
void mergeSort(vector<Comparable> & a, vector<Comparable> & tmpArray, int left, int right)
{
	cout << "Left = " << left << ", Right = " << right << endl;
	// printVector(a);

	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, tmpArray, left, center);
		mergeSort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}

/**
 * Mergesort algorithm (driver).
 */
template<typename Comparable>
void mergeSort(vector<Comparable> & a)
{
	vector<Comparable> tmpArray(a.size());
	mergeSort(a, tmpArray, 0, a.size() - 1);
}

void printVector(vector<int> & h)
{
	unsigned int i;
	cout << "[";
	for (i = 0; i < h.size() - 1; ++i)
	{
		cout <<  h[i] << ",";
	} // end for
	cout <<  h[i] << "]" << endl;
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
	h[6] = 97;
	h[7] = 81;
	h[8] = 91;
	h[9] = 79;
	h[10] = 36;
	h[11] = 54;
	h[12] = 5;
	h[13] = 77;

	printVector(h);
	cout << "Start Sorting:" << endl;
	mergeSort(h);
	cout << "Ended Sorting:" << endl;
	printVector(h);
	return 0;
}
