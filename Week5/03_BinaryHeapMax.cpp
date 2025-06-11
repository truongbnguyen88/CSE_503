#include <iostream>
#include <vector>
using namespace std;

class UnderflowException
{
};

template<typename Comparable>
class BinaryHeap
{
	public:
		explicit BinaryHeap(int capacity = 100) : array(capacity + 1), currentSize(0)
		{
		}

		explicit BinaryHeap(const vector<Comparable> & items) :
			array(items.size() + 10), currentSize(items.size())
		{
			for (int i = 0; i < items.size(); i++)
				array[i + 1] = items[i];
			buildHeap();
		}

		bool isEmpty() const
		{
			return currentSize == 0;
		}

		/**
		 * Find the largest item in the priority queue.
		 * Return the largest item, or throw Underflow if empty.
		 */
		const Comparable & findMax() const
		{
			if (isEmpty())
				throw UnderflowException();
			return array[1];
		}
		/**
		 * Insert item x, allowing duplicates.
		 */
		void insert(const Comparable & x)
		{
			cout << "Inserting " << x << endl;
			if (currentSize == array.size() - 1)  // If close to end
				array.resize(array.size() * 2);	  // we double the size

			// Percolate up
			int hole = ++currentSize;
			for (; hole > 1 && x > array[hole / 2]; hole /= 2)
			{
				cout << "Since x = " << x <<  " greater than a[" << hole / 2 << "] = "  << array[hole / 2] << 
					   ", we switch " << x <<  " with "  << array[hole / 2] << endl;
				array[hole] = array[hole / 2];
			}
			array[hole] = x;
			printHeap();
			cout << "__________________" << endl;
		}

		/**
		 * Remove the minimum item.
		 * Throws UnderflowException if empty.
		 */
		void deleteMax()
		{
			if (isEmpty())
				throw UnderflowException();
			cout << "Deleting " << array[1] << endl;
			array[1] = array[currentSize--];
			percolateDown(1);
		}

		/**
		 * Remove the maximum item and place it in minItem.
		 * Throws Underflow if empty.
		 */
		void deleteMax(Comparable & minItem)
		{
			if (isEmpty())
				throw UnderflowException();

			minItem = array[1];
			array[1] = array[currentSize--];
			percolateDown(1);
		}

		void makeEmpty()
		{
			currentSize = 0;
		}

		void printHeap()
		{
			unsigned int i;
			cout << "[";
			for (i = 0; i < currentSize; ++i)
			{
				cout <<  array[i] << ",";
			} // end for
			cout <<  array[i] << "]" << endl;
		}

	private:
		vector<Comparable> array; // The heap array
		unsigned currentSize; // Number of elements in heap


		/**
		 * Establish heap order property from an arbitrary
		 * arrangement of items. Runs in linear time.
		 */
		void buildHeap()
		{
			for (int i = currentSize / 2; i > 0; i--)
				percolateDown(i);
		}

		/**
		 * Internal method to percolate down in the heap.
		 * hole is the index at which the percolate begins.
		 */
		void percolateDown(unsigned hole)
		{
			unsigned child;
			Comparable tmp = array[hole];
			printHeap();
			// As long as the hole I am at has a left child 
			// I will continue to loop.
			// Notice that when I increment the loop I jump up the array
			// to the child of the current hole.
			for (; hole * 2 <= currentSize; hole = child) 
			{	
				child = hole * 2;  // This is left child occupying the array at 1
				if (child != currentSize)
				{
					cout << "The parent is " << array[hole] << endl;
					cout << "The left child is " << array[child] << 
						" and the right child is " << array[child+1] << endl;
				}
				else
				{
					cout << "The parent is " << array[hole] << endl;
					cout << "The left child is " << array[child] << endl;
				} 
				if (child != currentSize && array[child + 1] > array[child])
				{
					// Did not tip outside "child != currentSize"
					// right child > left child "array[child + 1] > array[child]"
					// Pick right child "child++"
					child++;
				} 		
				if (array[child] > tmp)
				{
					cout << "Swapping " << tmp << " with " << array[child] << endl;
					array[hole] = array[child];
					array[child] = tmp;
				}
				else
				{
					cout << "No swapping neccessary  " << endl;
					break;
				}
			}
			array[hole] = tmp;
			printHeap();
			cout << "__________________" << endl;
		}
};

int main()
{
	BinaryHeap<int> h(8);
	h.insert(31);
	h.insert(41);
	h.insert(59);
	h.insert(26);
	h.insert(53);
	h.insert(58);
	h.insert(97);
	cout << "=====================================" << endl;
	h.deleteMax();
	h.deleteMax();
	h.deleteMax();

	
	//  	BinaryHeap<int> h(9);
	// h.insert(7);
	// h.insert(5);
	// h.insert(3);
	// h.insert(1);
	// h.insert(8);
	// h.insert(6);
	// h.insert(4);
	// h.insert(2);
	// cout << "=====================================" << endl;
	// h.printHeap();
	// h.deleteMax();
	// h.printHeap();
	
	return 0;
}
