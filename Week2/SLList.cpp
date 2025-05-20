/**
 * A sample code of Creating C++ linked lists,
 * Including definitions the list node class and linked list class,
 * and how to create a blank linked list and a one-node linked list.
 *
 * Outline: understand the definition and structure of the linked
 * list and build a linked list based on it.
 */

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;




/* definition of the list node class */
class Node
{
    friend class LinkedList;
private:
    int value; 
    Node *pPrev;
    Node *pNext;
    
public:
    /* Constructors with No Arguments */
    Node(void)
    : pNext(NULL)
    { }
    
    /* Constructors with a given value */
    Node(int val)
    : value(val), pPrev(NULL), pNext(NULL)
    { }
    
    /* Constructors with a given value and a link of the next node */
    Node(int val, Node* prev, Node* next)
    : value(val), pPrev(prev), pNext(next)
    {}
    
    /* Getters */
    int getValue(void)
    { return value; }
    
    Node* getNext(void)
    { return pNext; }

    Node* getPrev(void)
    { return pPrev; }
};

/* definition of the linked list class */
class LinkedList
{
private:
    /* pointer of head node */
    Node *pHead;
    /* pointer of tail node */
    Node *pTail;
    
public:
    /* Constructors with No Arguments */
    LinkedList(void);
    /* Constructors with a given value of a list node */
    LinkedList(int val);
    /* Destructor */
    ~LinkedList(void);
    
    /* Traversing the list and printing the value of each node */
    void traverse_and_print();

    /* Traversing the list from tail to head and print.
       This is to check that we can access parent node of current node 
    */
    void print_from_tail_to_head();
	
	void push_back(int val);
};

LinkedList::LinkedList()
{
    /* Initialize the head and tail node */
    pHead = pTail = NULL;
}

LinkedList::LinkedList(int val)
{
    /* Create a new node, acting as both the head and tail node */
    pHead = new Node(val);
    pTail = pHead;
}

LinkedList::~LinkedList()
{
    
}

void LinkedList::traverse_and_print()
{
    Node *p = pHead;
    
    /* The list is empty? */
    if (pHead == NULL) {
        cout << "The list is empty" << endl;
        return;
    }
    
    cout << "LinkedList: ";
    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        cout << p->value << " ";
        /* The pointer moves along to the next one */
        p = p->pNext;
    }
    cout << endl;
}

void LinkedList::print_from_tail_to_head()
{
    Node *p = pTail;
    /* The list is empty? */
    if (pTail == NULL) {
        cout << "The list is empty" << endl;
        return;
    }

    cout << "LinkedList (from tail node to head node): ";
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        cout << p->value << " ";
        /* The pointer moves along to the next one */
        p = p->pPrev;
    }
    cout << endl;
}

// /* This code works for single linklist */
// void LinkedList::push_back(int val){
// 	/*Your code here*/
// 	Node * p = new Node(val);
//     // handle the case where LinkList is empty
//     if (pHead == NULL) {
//         pHead = pTail = p; // if empty list then set pHead = pTail to be node p i.e., p is new-node acting as head and tail
//     } else {
//         pTail->pNext = p; // if not empty list we put new_node p at the end & link it to next node of pTail
//         pTail = p;        // then update pTail to be new_node p
//     }
// }

/* This code is modified to work with double linklist */
void LinkedList::push_back(int val){
	/*Your code here*/
	Node * p = new Node(val);
    // handle the case where LinkList is empty
    if (pHead == NULL) {
        pHead = pTail = p; // if empty list then set pHead = pTail to be node p i.e., p is new-node acting as head and tail
    } else {
        pTail->pNext = p; // if not empty list we put new_node p at the end & link it to next node of pTail
        p->pPrev = pTail; // link prev. of p to pTail
        pTail = p;        // then update pTail to be new_node p
    }
}

int main(int argc, const char * argv[])
{
    /* Create an empty list */
    LinkedList list1;
    cout << "Created an empty list named list1." << endl;
    /* output the result */
    cout << "list1:" << endl;
    list1.traverse_and_print();
    
    /* Create a list with only one node */
    LinkedList list2(10);
    cout << "Created a list named list2 with only one node." << endl;
    /* output the result */
    cout << "list2:" << endl;
    list2.traverse_and_print();
	
	/*your testing code here*/
	for (int i = 0 ; i < 10; i++){
		list2.push_back(i);
	}
	list2.traverse_and_print();
    list2.print_from_tail_to_head();
    return 0;
}
