#include <iostream>
#include <vector>

using namespace std;

void printRow(vector<int> & h)
{
	unsigned int i;
	cout << "[";
	for (i = 0; i < h.size() - 1; ++i)
	{
		cout <<  h[i] << ",";
	} // end for
	cout <<  h[i] << "]" << endl;
}

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild(int i)
{
	return 2 * i + 1;   // This was 2*i 
}

/**
 * Internal method for heapsort that is used in deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template<typename Comparable>
void percDown(vector<Comparable> & a, int i, int n)
{
	int child;
	Comparable tmp;
	cout << endl;
	cout << "Starting the case for i = " << i << endl;
	for (tmp = a[i]; leftChild(i) < n; i = child)
	{
		printRow(a);
		child = leftChild(i);
		cout << "The parent is " << a[i] << endl;
		cout << "The left child is " << a[child] << " and the right child is " << a[child+1] << endl;
		if (child != n - 1 && a[child] < a[child + 1])
		{
			child++;
			cout << "The maximum of the two children is " << a[child] << endl;
		}	
		if (tmp < a[child])
		{	
			cout << "Swapping " << tmp << " with " << a[child] << endl;
			a[i] = a[child];

		}
		else
		{
			cout << "No swapping neccessary  " << endl;
			break;	
		}
	}
	a[i] = tmp;
	printRow(a);
}

template<typename Comparable>
void heapsort(vector<Comparable> & a)
{
	printRow(a);
	cout << "Start Building the Heap:" << endl;
	for (int i = a.size() / 2; i >= 0; i--) /* buildHeap */
	{
		percDown(a, i, a.size());
	}
	cout << "++++++++++++++++Ended Building the Heap:" << endl << endl;
	cout << "Start Sorting the Heap:" << endl;
	for (int j = a.size() - 1; j > 0; j--)
	{
		cout << "Deleting " << a[0] << " and swapping it with " << a[j] << endl;
		swap(a[0], a[j]); /* deleteMax */
		printRow(a);
		percDown(a, 0, j);
	}
	cout << "Ended Sorting the Heap:";
}

int main()
{

	vector<int> h(9);


	h[0] = 31;
	h[1] = 41;
	h[2] = 59;
	h[3] = 26;
	h[4] = 53;
	h[5] = 58;
	h[6] = 97;
	h[7] = 101;
	h[8] = -21;

	heapsort(h);

	return 0;

}
