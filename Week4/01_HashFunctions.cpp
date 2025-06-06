//============================================================================
// Name        : 01_HashFunctions.cpp
// Author      : Ibrahim Imam
// Version     :
// Copyright   : See textbook for course
// Description : Hello World in C++, Ansi-style
// These are my CECS 302 Fall 2014 students
//============================================================================

#include <iostream>
using namespace std;

int hash_0(const int &, int);
int hash_1(const string &, int);
int hash_2(const string &, int);
int hash_3(const string &, int);

int main()
{
	int tableSize = 56;
	int itemsCount = 86;
	string myName[86];

	myName[0] = "Banjanovic";
	myName[1] = "Amante";
	myName[2] = "Arumugam";
	myName[3] = "Balser";
	myName[4] = "Bass";
	myName[5] = "Baxter";
	myName[6] = "Burks";
	myName[7] = "Caldwell";
	myName[8] = "Combs";
	myName[9] = "Conrad";
	myName[10] = "Cox";
	myName[11] = "Dashner";
	myName[12] = "Decker";
	myName[13] = "Disibio";
	myName[14] = "Dockery";
	myName[15] = "Doninger";
	myName[16] = "Dwelee";
	myName[17] = "Emmons";
	myName[18] = "Everidge";
	myName[19] = "Eveslage";
	myName[20] = "Exe";
	myName[21] = "Faulk";
	myName[22] = "Ford";
	myName[23] = "Fuller";
	myName[24] = "Glass";
	myName[25] = "Hall";
	myName[26] = "Hamilton";
	myName[27] = "Harris";
	myName[28] = "Hemmelgarn";
	myName[29] = "Higdon";
	myName[30] = "Hinkle";
	myName[31] = "Hora";
	myName[32] = "Hughes";
	myName[33] = "Hundley";
	myName[34] = "Jackson";
	myName[35] = "Jenkins";
	myName[36] = "Joy";
	myName[37] = "Judy";
	myName[38] = "Kastensmidt";
	myName[39] = "Kim";
	myName[40] = "Le";
	myName[41] = "Lentz";
	myName[42] = "Lindley";
	myName[43] = "Lutes";
	myName[44] = "Maddox";
	myName[45] = "Markwell";
	myName[46] = "Martin";
	myName[47] = "Masden";
	myName[48] = "Matchuny";
	myName[49] = "McClellan";
	myName[50] = "McCullough";
	myName[51] = "Meyer";
	myName[52] = "Motill";
	myName[53] = "Naidu";
	myName[54] = "Nix";
	myName[55] = "Olges";
	myName[56] = "Owen";
	myName[57] = "Patel";
	myName[58] = "Patel";
	myName[59] = "Patel";
	myName[60] = "Pemberton";
	myName[61] = "Pitchford";
	myName[62] = "Robertson";
	myName[63] = "Rudd";
	myName[64] = "Schaal";
	myName[65] = "Schalk";
	myName[66] = "Scheper";
	myName[67] = "Schieman";
	myName[68] = "Schroll";
	myName[69] = "Seeforth";
	myName[70] = "Shepard";
	myName[71] = "Shepherd";
	myName[72] = "Smith";
	myName[73] = "Stargel";
	myName[74] = "Stout";
	myName[75] = "Stromberg";
	myName[76] = "Tapley";
	myName[77] = "Thomas";
	myName[78] = "Thompson";
	myName[79] = "Tucker";
	myName[80] = "Tumburu";
	myName[81] = "Twohey";
	myName[82] = "Vogelsang";
	myName[83] = "Weston";
	myName[84] = "Wilcox";
	myName[85] = "Zinner";

	cout << endl << "Items Count = " << itemsCount << ", Table Size = " << tableSize << endl;
	cout << "Key Value,\t " << "hash_1 value \t " << "hash_2 value \t " << "hash_3 value" << endl;
	for (int i = 0; i < itemsCount; ++i)
	{
		cout << myName[i] << ",\t\t\t " << hash_1(myName[i], tableSize) << ",\t\t\t " << hash_2(myName[i], tableSize) << ",\t\t\t "
				<< hash_3(myName[i], tableSize) << endl;
	} // end for

	cout << endl;
	cout << hash_0(11, 4) << endl;
	cout << hash_0(16, 4) << endl;
	cout << hash_0(7, 4) << endl;
	cout << hash_0(9, 4) << endl;
	cout << hash_0(13, 4) << endl;
	cout << hash_0(6, 4) << endl;

	cout << hash_0(200, 13) << endl;
	cout << hash_0(670, 13) << endl;
	cout << hash_0(8970, 13) << endl;
	return 0;
}

int hash_0(const int & key, int tableSize)
{
	return (key*7 + 3) % tableSize;
}

int hash_1(const string & key, int tableSize)
{
	int hashVal = 0;
	for (unsigned i = 0; i < key.length(); i++)
	{
		hashVal += key[i]; // take the ASCII value of each character
	} // end for
	return hashVal % tableSize;
}

int hash_2(const string & key, int tableSize)
{
	return (key[0] + 27 * key[1] + 729 * key[2]) % tableSize;
}

int hash_3(const string & key, int tableSize)
{
	int hashVal = 0;

	for (unsigned i = 0; i < key.length(); i++)
	{
		hashVal = 37 * hashVal + key[i]; // could become very large --> create overflow and become negative
	} // end for

	hashVal %= tableSize;
	if (hashVal < 0)
	{
		hashVal += tableSize;
	} // end if
	return hashVal;
}
