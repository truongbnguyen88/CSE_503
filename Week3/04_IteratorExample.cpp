#include<iostream>
#include<vector>

using namespace std;

class person
{
	public:
		person(); // default constructor
		person(const person &); // copy constructor
		~person(); // destructor

		void SetAge(int inAge)
		{
			*age = inAge;
		}
		int GetAge() const
		{
			return *age;
		}
		void SetWeight(int inWeight)
		{
			*weight = inWeight;
		}

		int GetWeight() const
		{
			return *weight;
		}

		void SetFirstName(string fn)
		{
			firstName = fn;
		}
		string GetFirstName() const
		{
			return firstName;
		}
		void SetLastName(string ln)
		{
			lastName = ln;
		}

		string GetLastName() const
		{
			return lastName;
		}

		person operator=(const person &);

	private:
		// notice both are pointers
		int *age;
		int *weight;
		string firstName;
		string lastName;
};
person::person()
{
	age = new int;
	weight = new int;
	firstName = "";
	lastName = "";
	*age = 0;
	*weight = 0;
}

person::person(const person & rhs)
{
	age = new int;
	weight = new int;
	*age = rhs.GetAge();
	*weight = rhs.GetWeight();
	firstName = rhs.GetFirstName();
	lastName = rhs.GetLastName();
}

person::~person()
{
	delete age;
	age = 0;
	delete weight;
	weight = 0;
}

person person::operator=(const person & rhs)
{
	if (this == &rhs)
		return *this;

	delete age;
	delete weight;
	age = new int;
	weight = new int;
	*age = rhs.GetAge();
	*weight = rhs.GetWeight();
	firstName = rhs.GetFirstName();
	lastName = rhs.GetLastName();
	return *this;
}

int main()
{
	person me;
	unsigned i = 5;
	vector<person>::iterator itr;
	vector<person>::const_iterator citr;
	vector<person> mes(i);

	me.SetAge(48);
	me.SetWeight(183);
	me.SetFirstName("Ibrahim");
	me.SetLastName("Imam");

	cout << "I am now " << me.GetAge() << endl;
	cout << "I weigh " << me.GetWeight() << endl;
	cout << "My Name is " << me.GetFirstName() << " " << me.GetLastName() << endl;

	person me2(me);
	cout << "I am now " << me2.GetAge() << endl;
	cout << "I weigh " << me2.GetWeight() << endl;
	cout << "My Name is " << me2.GetFirstName() << " " << me2.GetLastName() << endl;
	cout << endl;

	for (i = 0; i < 5; ++i)
	{
		mes[i] = me;
		mes[i].SetAge(me.GetAge() - i * 5);
		mes[i].SetWeight(me.GetWeight() + i * 5);
		cout << "I am now " << mes[i].GetAge() << " and I weigh " << mes[i].GetWeight() << endl;
	}
	cout << endl;

	i = 0;

	for (itr = mes.begin(); itr != mes.end(); ++itr)
	{
		itr->operator =(me);
		itr->SetAge(me.GetAge() + i * 5);
		itr->SetWeight(me.GetWeight() - i * 5);
		i++;
	}
	cout << endl;

	for (citr = mes.begin(); citr != mes.end(); ++citr)
	{
		cout << "In the cItr. I am " << citr->GetAge() << " and I weigh " << citr->GetWeight() << endl;
	}

	return 0;
}
