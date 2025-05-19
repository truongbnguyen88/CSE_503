#include <iostream>
using namespace std;

template<typename Container>
void printCollection(const Container & c, ostream & out = cout)
{
	if (c.empty())
	{
		out << "(empty)";
	}
	else
	{
		typename Container::const_iterator itr = c.begin();
		out << "[ " << *itr++; // Print first item
		while (itr != c.end())
		{
			out << ", " << *itr++;
		} // end while
		out << " ]" << endl;
	} // end ifelse

}

template<typename Object>
class Vector
{
	public:
		// constructor for a new vector with default initSize of 0
		// theSize is set to initSize (recall: theSize = (private) class variable)
		// theCapacity is set to initSize + SPARE_CAPACITY  (recall: SPARE_CAPACITY = (private) class variable; default value to be 16)
		explicit Vector(int initSize = 0) : theSize(initSize), theCapacity(initSize + SPARE_CAPACITY)
		{
			objects = new Object[theCapacity]; // initialize new objects with size = theCapacity
		}
		// copy constructor: initialize with some existing vector
		Vector(const Vector & rhs) : objects(NULL)
		{
			operator=(rhs);
		}
		// destructor
		~Vector()
		{
			delete[] objects;
		}

		// copy a vector (by using operator equal), pass by reference some rhs vector
		const Vector & operator=(const Vector & rhs)
		{
			// if the object is not equal rhs, then delete object
			// and set theSize and theCapacity to be size and capacity of rhs
			if (this != &rhs)
			{
				delete[] objects;
				theSize = rhs.size();
				theCapacity = rhs.theCapacity;

				objects = new Object[capacity()];
				// copy all entries in rhs to new object, one-by-one
				for(int k = 0; k < size(); k++)
				{
					objects[k] = rhs.objects[k];
				} // end for

			}
			return *this;
		}

		// resize the vector object by reserve memory by 2X of newSize
		// then set variable theSize to the newSize
		void resize(int newSize)
		{
			if (newSize > theCapacity)
			{
				reserve(newSize * 2 + 1);
			} // end if

			theSize = newSize;
		}

		// implementation of reserve function
		void reserve(int newCapacity)
		{
			// if newCapacity less than theSize, then we don't do anything
			if (newCapacity < theSize)
			{
				return;
			} // end if

			// if newCapacity >= the current size of vector (theSize) then
			// create new object with newCapacity and copy the fill new object with 
			// values of the old vector object (in the first 'theSize' position)
			Object *oldArray = objects;

			objects = new Object[newCapacity];
			for (int k = 0; k < theSize; k++)
			{
				objects[k] = oldArray[k];
			} // end for
			// set theCapacity variable to be equal to newCapacity
			theCapacity = newCapacity;
			// delete oldArray since it serves as intermediate variable
			delete[] oldArray;
		}

		// accessing operator: access Vector element at 'index'
		Object & operator[](int index)
		{
			return objects[index];
		}
		const Object & operator[](int index) const
		{
			return objects[index];
		}

		bool empty() const
		{
			return size() == 0; // check if size() of Vector is zero i.e., is Vector empty or not?
		}
		int size() const
		{
			return theSize; // return size of Vector
		}
		int capacity() const
		{
			return theCapacity; // return capacity of Vector
		}

		// add an element/object x at the end of vector
		void push_back(const Object & x)
		{
			if (theSize == theCapacity)
			{
				reserve(2 * theCapacity + 1); // if capacity = size of vector, we need to reserve more memory for x
			} // end if
			objects[theSize++] = x; // put x at the end i.e., at index theSize+1
		}

		void pop_back()
		{
			theSize--; // reduce size of Vector by 1 <=> remove last element of Vector
		}

		const Object & back() const
		{
			return objects[theSize - 1]; // access the last element of Vector
		}

		// define iterator and constant iterator to be pointers (point to some pieces of memory)
		typedef Object * iterator;
		typedef const Object * const_iterator;

		iterator begin()
		{
			return &objects[0]; // using iterator to get first element of Vector
		}
		const_iterator begin() const
		{
			return &objects[0]; // using constant iterator to get first element of Vector
		}
		iterator end()
		{
			return &objects[size()]; // using iterator to get last element of Vector
		}
		const_iterator end() const
		{
			return &objects[size()]; // using constant iterator to get last element of Vector
		}

		enum
		{
			SPARE_CAPACITY = 16
		};

		private:
		int theSize;
		int theCapacity;
		Object * objects;
	};

int main()
{
	// initialize myV using class Vector
	Vector<int> myV(10);

	for(int i = 0; i < myV.size(); i++)
	{
		myV[i] = int(3*i); // fill vector with entries: 0,3,6,9,...,27=3*9
	} // end for
	printCollection(myV, cout); // print all elements in myV
	myV.push_back(91);			// insert 91 at the end of myV
	printCollection(myV, cout); // re-print all elements in myV
	myV.pop_back();				// remove the very last element of myV
	printCollection(myV, cout); // re-print all elements in myV
	cout << "The Capacity: " << myV.capacity() << endl;
	cout << "The Size:     " << myV.size() << endl;
	cout << "The begining: " << *myV.begin() << endl;
	
	// create an iterator object called myItr and set it to be beginning element of myV
	Vector<int>::iterator myItr = myV.begin();
	cout << "current value that myItr point to = " << *myItr << endl;
	/* Note to Truong: recall that iterator/constant_iterator is defined to be pointer in class Vector
	   so when we print(myItr) it will display memory location not the value that myItr points to!
	   To extract the value of Vector myV that myItr points to, we need to print(*myItr)
	*/
	myItr = myItr + 3; // increase iterator by 3 positions
	cout << "The current value that myItr point to = " << *myItr << endl;
	for (unsigned i = 0; i < 3; ++i)
	{
		myItr++; // get current value of myV (using iterator myItr) and move iterator to the next position
		cout << "The current value that myItr point to = " << *myItr << endl;
	} // end for
	cout << "The current value that myItr point to = " << *myItr << endl;

	return 0;
}

