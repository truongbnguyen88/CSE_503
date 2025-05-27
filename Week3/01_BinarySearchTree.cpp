#include <iostream>
using namespace std;

template<typename Comparable>
class BinarySearchTree
{
	public:
		BinarySearchTree()
		{
			root = NULL;
		}
		BinarySearchTree(const BinarySearchTree & rhs);
		/**
		 * Destructor for the tree
		 */
		~BinarySearchTree()
		{
			makeEmpty();
		}

		const Comparable & findMin() const
		{
			return findMin(root);
		}

		const Comparable & findMax() const
		{
			return findMax(root);
		}

		/**
		 * Returns true if x is found in the tree.
		 */
		bool contains(const Comparable & x) const
		{
			return contains(x, root);
		}

		bool isEmpty() const
		{
			return ((root == NULL) ? true : false);
		}
		/**
		 * Print the tree contents in sorted order.
		 */
		void printTree(ostream & out = cout) const
		{
			out << "Start Traversing" << endl;
			if (isEmpty())
				out << "Empty tree" << endl;
			else
				printTree(root, out);
			out << "End Traversing" << endl;
		}

		void makeEmpty()
		{
			makeEmpty(root);
		}
		/**
		 * Insert x into the tree; duplicates are ignored.
		 */
		void insert(const Comparable & x)
		{
			insert(x, root);
		}

		/**
		 * Remove x from the tree. Nothing is done if x is not found.
		 */
		void remove(const Comparable & x)
		{
			remove(x, root);
		}

		/**
		 * Deep copy.
		 */
		const BinarySearchTree & operator=(const BinarySearchTree & rhs)
		{
			if (this != &rhs)
			{
				makeEmpty();
				root = clone(rhs.root);
			}
			return *this;
		}

	private:
		struct BinaryNode
		{
				Comparable element;
				BinaryNode *left;
				BinaryNode *right;

				BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt) :
						element(theElement), left(lt), right(rt)
				{
				}
		};

		BinaryNode *root;

		/**
		 * Internal method to insert into a subtree.
		 * x is the item to insert.
		 * t is the node that roots the subtree.
		 * Set the new root of the subtree.
		 */
		void insert(const Comparable & x, BinaryNode * & t)
		{
			if (t == NULL)
				t = new BinaryNode(x, NULL, NULL);
			else if (x < t->element)
				insert(x, t->left);
			else if (t->element < x)
				insert(x, t->right);
			else
				; // Duplicate; do nothing
		}
		/**
		 * Internal method to remove from a subtree.
		 * x is the item to remove.
		 * t is the node that roots the subtree.
		 * Set the new root of the subtree.
		 */
		void remove(const Comparable & x, BinaryNode * & t)
		{
			if (t == NULL)
				return; // Item not found; do nothing
			if (x < t->element)
				remove(x, t->left);
			else if (t->element < x)
				remove(x, t->right);
			else if (t->left != NULL && t->right != NULL) // Two children
			{
				t->element = findMin(t->right)->element; // find smallest in right subtree
				remove(t->element, t->right);
			}
			else
			{
				BinaryNode *oldNode = t;
				t = (t->left != NULL) ? t->left : t->right; // Replace t with its left child if it exists, otherwise use its right child.
				delete oldNode;
			}
		}
		/**
		 * Internal method to find the smallest item in a subtree t.
		 * Return node containing the smallest item.
		 */
		// Since lesser-value elements are always on the left, we can find the minimum by traversing left.
		// If the left child is NULL, then we have found the minimum.
		// If the left child is not NULL, we continue traversing left until we reach a NULL left child.
		// This is a recursive approach to find the minimum element in a binary search tree.
		BinaryNode * findMin(BinaryNode *t) const
		{
			if (t == NULL)
				return NULL;
			if (t->left == NULL)
				return t;
			return findMin(t->left);
		}
		/**
		 * Internal method to find the largest item in a subtree t.
		 * Return node containing the largest item.
		 */
		// Since greater-value elements are always on the right, we can find the maximum by traversing right.
		// If the right child is NULL, then we have found the maximum.
		// If the right child is not NULL, we continue traversing right until we reach a NULL right child.
		// This is a recursive approach to find the maximum element in a binary search tree.
		BinaryNode * findMax(BinaryNode *t) const
		{
			if (t != NULL)
				while (t->right != NULL)
					t = t->right;
			return t;
		}

		/**
		 * Internal method to test if an item is in a subtree.
		 * x is item to search for.
		 * t is the node that roots the subtree.
		 */
		bool contains(const Comparable & x, BinaryNode *t) const
		{
			if (t == NULL)
				return false;
			else if (x < t->element) // If x is less than the current node's element, search in the left subtree.
				return contains(x, t->left);
			else if (t->element < x) // If x is greater than the current node's element, search in the right subtree.
				return contains(x, t->right);
			else
				return true; // Match
		}
		/**
		 * Internal method to make subtree empty.
		 */
		void makeEmpty(BinaryNode * & t)
		{
			if (t != NULL)
			{
				makeEmpty(t->left);
				makeEmpty(t->right);
				delete t;
			}
			t = NULL;
		}
		/**
		 * Internal method to compute the height of a subtree rooted at t.
		 */
		// The height of a binary tree is the number of edges on the longest path from the root to a leaf node.
		// If the tree is empty, the height is -1.
		// If the tree is not empty, the height is 1 plus the maximum height of its left and right subtrees.
		int height(BinaryNode *t)
		{
			if (t == NULL)
				return -1;
			else
				return 1 + max(height(t->left), height(t->right));
		}
		/**
		 * Internal method to print a subtree rooted at t in sorted order.
		 */
		void printTree(BinaryNode *t, ostream & out) const
		{
			if (t != NULL)
			{
				// out << t->element << "\n";
				printTree(t->left, out);
				// out << t->element << "\n";
				printTree(t->right, out);
				out << t->element << "\n";
			}
		}
		/**
		 * Internal method to clone subtree.
		 */
		BinaryNode * clone(BinaryNode *t) const
		{
			if (t == NULL)
				return NULL;

			return new BinaryNode(t->element, clone(t->left), clone(t->right));
		}
};

int main()
{
	cout << "Starting!" << endl;

	BinarySearchTree<int> myTree;

	myTree.insert(11);
	cout << "Inserted  11" << endl;
	myTree.insert(12);
	cout << "Inserted 12" << endl;
	myTree.insert(6);
	cout << "Inserted  6" << endl;
	myTree.insert(8);
	cout << "Inserted  8" << endl;
	myTree.insert(7);
	cout << "Inserted  7" << endl;
	myTree.insert(9);
	cout << "Inserted  9" << endl;
	myTree.insert(2);
	cout << "Inserted  2" << endl;
	myTree.insert(4);
	cout << "Inserted  4" << endl;
	myTree.insert(10);
	cout << "Inserted  10" << endl;
	myTree.insert(5);
	cout << "Inserted  5" << endl;
	myTree.insert(14);
	cout << "Inserted  14" << endl;
	myTree.insert(13);
	cout << "Inserted  13" << endl;

	myTree.printTree(cout);
	myTree.remove(13);
	cout << "Removed  13" << endl;
	myTree.printTree(cout);
	myTree.insert(5);
	cout << "Inserted  5" << endl;
	myTree.printTree(cout);
	cout << "Ending!" << endl;
	return 0;
}
