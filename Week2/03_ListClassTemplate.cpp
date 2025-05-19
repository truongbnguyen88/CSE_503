//============================================================================
// Name        : 03_ListClassTemplate.cpp
// Author      : Mark Weiss
// Description : List Class Template
//============================================================================

#include <iostream>
#include <iterator>
using namespace std;

template<typename Container>
void printCollection(const Container & c, ostream & out = cout)
{
	if (c.empty())
		out << "(empty)";
	else
	{
		typename Container::const_iterator itr = c.begin();
		out << "[ " << *itr++; // Print first item
        
		while (itr != c.end())
			out << ", " << *itr++;
		out << " ]" << endl;
	}
}


template <typename Object>
class List
{
private:

    /* Node structur has following: 
        - data contains values of node
        - previous pointer *prev that points to previous node
        - next     pointer *next that points to the next node
    */
    struct Node
    {
        Object  data;
        Node   *prev;
        Node   *next;
        
        Node( const Object & d = Object( ), Node * p = NULL, Node * n = NULL )  : data( d ), prev( p ), next( n ) { }
    };
    
   
    public:
        class const_iterator
        {
        public:
            
            // Public constructor for const_iterator.
            const_iterator( ) : current( NULL )
            { }
            
            // Return the object stored at the current position.
            // For const_iterator, this is an accessor with a
            // const reference return type.
            const Object & operator* ( ) const
            { return retrieve( ); }
            
            // usage: ++itr : pre-increment: increase iterator first then return increamented value
            const_iterator & operator++ ( )
            {
                current = current->next;
                return *this;
            }
            
            // usage: itr++ : post increment: return current value first then increase iterator
            const_iterator operator++ ( int )
            {
                const_iterator old = *this;
                ++( *this );
                return old;
            }
            
            // usage: --itr : pre-decrement: decrease iterator first then return decremented value
            const_iterator & operator-- ( )
            {
                current = current->prev;
                return *this;
            }
            
            // usage itr-- : post-decrement: return current value (that itr points to) then decrease iterator
            const_iterator operator-- ( int )
            {
                const_iterator old = *this;
                --( *this );
                return old;
            }
            
            // check if iterator is equal or not equal to some constant iterator
            bool operator== ( const const_iterator & rhs ) const
            { return current == rhs.current; }
            
            bool operator!= ( const const_iterator & rhs ) const
            { return !( *this == rhs ); }
            
        protected:
            Node *current;
            
            // Protected helper in const_iterator that returns the object
            // stored at the current position. Can be called by all
            // three versions of operator* without any type conversions.
            Object & retrieve( ) const
            { return current->data; }
            
            // Protected constructor for const_iterator.
            // Expects a pointer that represents the current position.
            const_iterator( Node *p ) :  current( p )
            { }
            
            friend class List<Object>;
        };
        
        class iterator : public const_iterator
        {
        public:
            
            // Public constructor for iterator.
            // Calls the base-class constructor.
            // Must be provided because the private constructor
            // is written; otherwise zero-parameter constructor
            // would be disabled.
            iterator( )
            { }
            
            Object & operator* ( )
            { return current->data; }
            
            // Return the object stored at the current position.
            // For iterator, there is an accessor with a
            // const reference return type and a mutator with
            // a reference return type. The accessor is shown first.
            const Object & operator* ( ) const
            { return const_iterator::operator*( ); }
            
            iterator & operator++ ( )
            {
                current = current->next;
                return *this;
            }
            
            iterator operator++ ( int )
            {
                iterator old = *this;
                ++( *this );
                return old;
            }
            
            iterator & operator-- ( )
            {
                current = current->prev;
                return *this;
            }
            
            iterator operator-- ( int )
            {
                iterator old = *this;
                --( *this );
                return old;
            }
            
        protected:

            Node *current;
            // Protected constructor for iterator.
            // Expects the current position.
            iterator( Node *p ) : const_iterator( p )
            { current = p;}
            
            friend class List<Object>;
        };
    
public:
    List( )
    { init( ); }
    
    ~List( )
    {
        clear( );
        delete head;
        delete tail;
    }
    
    List( const List & rhs )
    {
        init( );
        *this = rhs;
    }
    
    const List & operator= ( const List & rhs )
    {
        if( this == &rhs )
            return *this;
        clear( );
        for( const_iterator itr = rhs.begin( ); itr != rhs.end( ); ++itr )
            push_back( *itr );
        return *this;
    }
    
    // Return iterator representing beginning of list.
    // Mutator version is first, then accessor version.
    iterator begin( )
    { return iterator( head->next ); }
    
    const_iterator begin( ) const
    { return const_iterator( head->next ); }
    
    // Return iterator representing endmarker of list.
    // Mutator version is first, then accessor version.
    iterator end( )
    { return iterator( tail ); }
    
    const_iterator end( ) const
    { return const_iterator( tail ); }
    
    // Return number of elements currently in the list.
    int size( ) const
    { return theSize; }
    
    // Return true if the list is empty, false otherwise.
    bool empty( ) const
    { return size( ) == 0; }
    
    // clear out the list: do this one element at a time
    void clear( )
    {
        while( !empty( ) )
            pop_front( );
    }
    
    // front, back, push_front, push_back, pop_front, and pop_back
    // are the basic double-ended queue operations.
    Object & front( )
    { return *begin( ); }
    
    const Object & front( ) const
    { return *begin( ); }
    
    Object & back( )
    { return *--end( ); }
    
    const Object & back( ) const
    { return *--end( ); }
    
    void push_front( const Object & x )
    { insert( begin( ), x ); }
    
    void push_back( const Object & x )
    { insert( end( ), x ); }
    
    void pop_front( )
    { erase( begin( ) ); }
    
    void pop_back( )
    { erase( --end( ) ); }
    
    // Insert x before itr.
    iterator insert( iterator itr, const Object & x )
    {
        Node *p = itr.current;
        theSize++;
        return iterator( p->prev = p->prev->next = new Node( x, p->prev, p ) );
    }
    
    // Erase item at itr.
    iterator erase( iterator itr )
    {
        Node *p = itr.current;
        iterator retVal( p->next );
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;
        
        return retVal;
    }
    
    // erase elements from iterator start to iterator end
    iterator erase( iterator start, iterator end )
    {
        for( iterator itr = start; itr != end; )
            itr = erase( itr );
        
        return end;
    }

    // swap 2 elements at iterator itr location
    // elements in list: ... [p-2] [p-1] [p] [p+1] [p+2] ...
    // This function will swap place of [p-1] and [p+1]
    void swapNeighbors(iterator itr)
    {
        Node *p = itr.current;
        Node *beforep = p->prev;
        Node *afterp = p->next;
        Node *swapHead = beforep->prev;
        Node *swapTail = afterp->next;
        
        p->next = beforep;
        p->prev = afterp;
        beforep->next = swapTail;
        beforep->prev = p;
        afterp->next = p;
        afterp->prev = swapHead;
        swapHead->next = afterp;
        swapTail->prev = beforep;
    }
    
private:
    int   theSize;
    Node *head;
    Node *tail;
    
    void init( )
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};


int main()
{
	List<int> myL;
	List<int>::iterator itrb;
	List<int>::iterator itre;
	List<int>::iterator itrc;
    
	myL.push_front(181);
	myL.push_front(132);
	myL.push_front(12);
	myL.push_back(-654);
	myL.push_back(54);
    
	cout << "List size = " << myL.size() << endl;
	cout << "List: ";
	printCollection(myL, cout);
	itrb = myL.begin();
	itre = myL.end();
	itrc = myL.begin();
	myL.insert(itrb, 77);
	myL.insert(itre, 897);
	printCollection(myL, cout);
    
	cout << *itrc << endl;
    
	List<int>::iterator itr = myL.begin();
    
    // make iterator points to the 4th element
	for (int j = 0; j < 4; j++)
    {
        itr++;
	}
    cout << "begin swaping neighbors of element: " << *itr << endl;
	myL.swapNeighbors(itr);
	printCollection(myL, cout);
    
    // end program
	return 0;
}
