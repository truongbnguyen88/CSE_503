#include <assert.h>
#include <iostream>

using namespace std;

typedef int Type;

enum Boolean
{
	False = 0, True
};

class Item
{
		friend class SLList;

	public:
		Type getVal()
		{
			return val;
		}

	private:
		Item(Type value, Item *item = 0)
		{
			val = value;
			next = item;
		}

		Type val;
		Item *next;
};

class SLList
{
	public:

		class Const_Iterator
		{
				friend class SLList;
			public:
				Item *current;
				Const_Iterator() :
					current(NULL)
				{
				}

				const Item & operator*() const
				{
					return *this->current;
				}

				Const_Iterator operator++()
				{
					current = current->next;
					return *this;
				}

				Const_Iterator operator++(int)
				{
					Const_Iterator old = *this;
					++(*this);
					return old;
				}

				bool operator==(const Const_Iterator & rhs)
				{
					return current == rhs.current;
				}
				bool operator!=(const Const_Iterator & rhs)
				{
					return !(*this == rhs);
				}

				Item retrieve() const
				{
					return current->val;
				}

				Const_Iterator(Item *p) :
					current(p)
				{
				}

		};

		class Iterator
		{
				friend class SLList;
			public:
				Item *current;
				Iterator() :
					current(NULL)
				{
				}

				const Item & operator*() const
				{
					return *this->current;
				}

				Iterator operator++()
				{
					current = current->next;
					return *this;
				}

				Iterator operator++(int)
				{
					Iterator old = *this;
					++(*this);
					return old;
				}

				bool operator==(const Iterator & rhs) const
				{
					return current == rhs.current;
				}
				bool operator!=(const Iterator & rhs)
				{
					return !(*this == rhs);
				}

				Item retrieve()
				{
					return current->val;
				}

				Iterator(Item *p) :
					current(p)
				{
				}
		};

		SLList()
		{
			list = 0;
		}
		~SLList()
		{
			remove();
		}

		void insert(Type someItem);
		void append(Type someItem);
		int remove(Type someItem);
		void remove();

		Item *atEnd();
		Item *head();
		Item *tail();

		Boolean isPresent(Type someItem);
		Boolean isEmpty();
		void display();

	private:
		Iterator iterator;
		Item *list;
		Item *atEndItem;
};

Boolean SLList::isEmpty()
{
	return list == 0 ? True : False;
}

void SLList::insert(Type val)
{
	Item *pt = new Item(val, list); // create new item put it in front of list
	assert(pt != 0);
	if (list == 0)
	{
		atEndItem = pt;
	}
	list = pt; // and point next top the list
}

Item *SLList::atEnd()
{
	if (list == 0)
	{
		return 0;
	}

	Item *prev, *curr;
	prev = curr = list;

	while (curr)
	{
		prev = curr;
		curr = curr->next;
	}
	return prev;
}

Item *SLList::tail()
{
	if (list == 0)
	{
		return 0;
	}

	Item *prev, *curr;
	prev = curr = list;

	while (curr)
	{
		prev = curr;
		curr = curr->next;
	}
	return prev;
}

Item *SLList::head()
{
	if (list == 0)
	{
		cout << "List is empty" << endl;
		return 0;
	}
	else
	{
		return list;
	} // end if
	return list;
}

void SLList::append(Type val)
{
	Item *pt = new Item(val);
	assert(pt != 0);
	if (list == 0)
	{
		list = pt;
	}
	else
	{
		atEndItem->next = pt;
	}
	atEndItem = pt;
}

void SLList::display()
{
	cout << "(";
	for (Item *pt = list; pt; pt = pt->next)
	{
		cout << pt->val << " ";
	} // end for
	cout << ")" << endl;
}

void SLList::remove()
{
	Item *pt = list;
	while (pt)
	{
		Item *temp = pt;
		pt = pt->next;
		delete temp;
	} // end while
	list = atEndItem = 0;
}

Boolean SLList::isPresent(Type item)
{
	Boolean rc = False;
	if (list != 0)
	{
		if (list->val == item || atEndItem->val == item)
		{
			rc = True;
		}
		else
		{
			Item *pt = list->next;
			for (; pt != atEndItem; pt = pt->next)
			{
				if (pt->val == item)
				{
					rc = True;
				} // end if
			} // end for
		} // end if
	} // end if
	return rc;
}
int SLList::remove(Type val)
{
	Item *pt = list;
	int cnt = 0;

	while (pt && pt->val == val)
	{
		Item *tmp = pt->next;
		delete pt;
		cnt++;
		pt = tmp;
	} // end while

	if ((list = pt) == 0)
	{
		atEndItem = 0;
		return cnt;
	} // end if

	Item *prv = pt;
	pt = pt->next;

	while (pt)
	{
		if (pt->val == val)
		{
			prv->next = pt->next;
			if (atEndItem == pt)
			{
				atEndItem = prv;
			} // end if
			delete pt;
			++cnt;
			pt = prv->next;
		}
		else
		{
			prv = pt;
			pt = pt->next;
		} // end if else
	} // end while
	return cnt;
}

int main()
{
	cout << "Single Linked List Example" << endl;
	const int size = 12;
	const int odd = 1;
	int ix = 0;
	SLList il;
	SLList::Iterator itr;

	if (il.isEmpty() != True || il.isPresent(1024) != False)
	{
		cerr << "List class internal error (1)" << endl;
	}
	else
	{
		cout << "Ok, empty list class" << endl;
	} // end ifelse

	il.remove(1024);
	il.display();

	for (ix = 0; ix < size; ++ix)
	{
		il.append(ix % 2 ? odd : ix);
	} // end for

	il.display();
	if (il.isEmpty() == False)
	{
		cout << " Head " << il.head()->getVal() << endl;
		cout << " Tail " << il.tail()->getVal() << endl;
	} // end if


	if (il.isPresent(odd) != True)
	{
		cerr << "List class internal error (2)" << endl;
	} // end if

	int odd_cnt = il.remove(odd);

	cout << odd_cnt << " items of value " << odd << " removed." << endl;

	il.display();
	if (il.isEmpty() == False)
	{
		cout << " Head " << il.head()->getVal() << endl;
		cout << " Tail " << il.tail()->getVal() << endl;
	} // end if


	for (ix = 0; ix < odd_cnt; ++ix)
	{
		il.insert(odd);
	} // end for


	il.display();
	if (il.isEmpty() == False)
	{
		cout << " Head " << il.head()->getVal() << endl;
		cout << " Tail " << il.tail()->getVal() << endl;
	} // end if

	for (itr = il.head(); itr != il.tail(); itr++)
	{
		cout << "Itr =  " << itr.current->getVal()<< endl;
	} // end for

	il.remove();
	il.display();
	if (il.isEmpty() == False)
	{
		cout << " Head " << il.head()->getVal() << endl;
		cout << " Tail " << il.tail()->getVal() << endl;
	} // end if




	return 0;
}

