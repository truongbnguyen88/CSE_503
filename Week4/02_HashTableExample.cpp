#include <iostream>
#include <vector>
#include <list>
#include <string>


using namespace std;

int inihash(const string &);
int nextPrime(int);

class HashTable
{
	public:
		explicit HashTable(int size = 10) :
				currentSize(0)
		{
			theLists.resize(size);
			cout << "The Hash Table size is " << theLists.size() << endl;
		}

		bool insert(const string & x)
		// given a key x, insert it into the hash table
		{
			list<string> &whichList = theLists[myhash(x)]; // extract which hole we are going to insert x in
			// Note: we use pass-by-reference here, so we can modify theLists directly through whichList.

			// begin searching for x in whichList from begin to end
			// if found x then we cannot insert it again, exit since x is already there.
			if (find(whichList.begin(), whichList.end(), x) != whichList.end())
			{
				return false;
			} // end if
			// otherwise, can insert to the back of whichList
			whichList.push_back(x);
			cout << "Inserted " << x << endl;
			// increase size and test if it exceeds the size of theLists
			// we wanna rehash: expand the vector
			if (++currentSize > theLists.size())
			{
				printList();
				rehash();
			} // end if
			return true;
		}

		void makeEmpty()
		{
			for (unsigned i = 0; i < theLists.size(); i++)
				theLists[i].clear();
		}

		bool contains(const string & x) const
		{
			const list<string> & whichList = theLists[myhash(x)];
			return find(whichList.begin(), whichList.end(), x) != whichList.end();
		}

		bool remove(const string & x)
		{
			list<string> &whichList = theLists[myhash(x)];
			list<string>::iterator itr = find(whichList.begin(), whichList.end(), x);

			if (itr == whichList.end())
				return false;

			whichList.erase(itr);
			--currentSize;
			return true;
		}
		void rehash()
		{
			cout << "I am rehashing" << endl;
			vector<list<string> > oldLists = theLists;

			// Create new double-sized, empty table
			theLists.resize(nextPrime(2 * theLists.size()));
			// clear every entry in theLists
			for (unsigned j = 0; j < theLists.size(); j++)
				theLists[j].clear();

			// Copy table over
			currentSize = 0;
			// loop over the size of oldLists (recall each entry of oldLists is a list of string)
			for (unsigned i = 0; i < oldLists.size(); i++)
			{
				// create an iterator for list_of_string ith in oldList
				list<string>::iterator itr = oldLists[i].begin();
				// go through the iterator and insert using defined insert() function
				// recall that insert() function will insert back to theLists
				while (itr != oldLists[i].end())
					insert(*itr++);
			}
		}

		void printList()
		{
			for (unsigned i = 0; i < theLists.size(); i++)
			{
				list<string> &whichList = theLists[i];
				if (theLists.size() != 0)
				{
					list<string>::iterator itr = whichList.begin();
					cout << i;
					while (itr != whichList.end())
					{
						cout << ",\t" << *itr << "\t";
						itr++;
					}
					cout << endl;
				}

			} // end for
		}

	private:
		vector<list<string> > theLists; // The array of Lists
		unsigned currentSize;

		int myhash(const string & x) const
		{
			int hashVal = inihash(x);

			hashVal %= theLists.size();
			if (hashVal < 0)
				hashVal += theLists.size();

			return hashVal;
		}
};

int main()
{
	HashTable H;

	int itemsCount = 34;
	string myName[34];

	myName[0] = "Banjanovic";
	myName[1] = "Buckley";
	myName[2] = "Callahan";
	myName[3] = "DeWilligen";
	myName[4] = "Fischbeck";
	myName[5] = "Fleischmann";
	myName[6] = "Heichelbech";
	myName[7] = "Kirtley";
	myName[8] = "Mccubbin";
	myName[9] = "Meisinger";
	myName[10] = "Milallos";
	myName[11] = "Ratliff";
	myName[12] = "Vessels";
	myName[13] = "Banjanovic";
	myName[14] = "Broadhurst";
	myName[15] = "Buckley";
	myName[16] = "Burgard";
	myName[17] = "Cook";
	myName[18] = "Cooley";
	myName[19] = "Durcan";
	myName[20] = "Fackler";
	myName[21] = "Godage";
	myName[22] = "Humphrey";
	myName[23] = "Kowsari";
	myName[24] = "McClure";
	myName[25] = "Peoples";
	myName[26] = "Pruitt";
	myName[27] = "Simmons";
	myName[28] = "Smith";
	myName[29] = "Summers";
	myName[30] = "Tafel";
	myName[31] = "Tyler";
	myName[32] = "Vilardell";
	myName[33] = "Yadav";

	for (int i = 0; i < itemsCount; ++i)
	{
		H.insert(myName[i]);
	} // end for

	H.printList();

	cout << "Does H contain Imam " << H.contains("Imam") << endl;
	cout << "Does H contain Fleischmann " << H.contains("Fleischmann") << endl;
	cout << "Does H contain DeWilligen " << H.contains("DeWilligen") << endl;
	cout << "Does H contain Ratliff " << H.contains("Ratliff") << endl;
	cout << "Does H contain Fischbeck " << H.contains("Fischbeck") << endl;

	return 0;
}

int inihash(const string & key)
{
	int hashVal = 0;

	for (unsigned i = 0; i < key.length(); i++)
	{
		hashVal = 41 * hashVal + key[i];
	} // end for

	return hashVal;
}

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime(int n)
{
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime(int n)
{
	if (n % 2 == 0)
		n++;

	for (; !isPrime(n); n += 2)
		;

	return n;
}
