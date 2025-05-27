#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

class Node {
    int value;
public:
    Node* left;       // left child
    Node* right;      // right child
    Node* p;          // parent
    Node(int data) {
        value = data;
        left = NULL;
        right = NULL;
        p  = NULL;
    }
    ~Node() {
    }
    int d() {
        return value; // get value of current node
    }
    // we implement this setValue() function to allow chaning the value of a node.
    void setValue(int newValue) {
        value = newValue;
    }
    void print() {
        std::cout << value << std::endl;
    }
};

void insert(Node * insert_node, Node * & tree_root){
	//Your code here
    // When tree_root is NULL, we can set the insert_node to be the root.
    if (tree_root == NULL) {
        tree_root = insert_node;
        return;
    }
    // If insert_node's value is less than the current node's value, we go to the left subtree.
    if (insert_node->d() < tree_root->d()) {        
        if (tree_root->left == NULL) {              // Put the insert_node on the left of tree_root if tree_root's left is NULL.
            tree_root->left = insert_node;
            insert_node->p = tree_root;             // Set the parent of the insert_node to the root node.
        } else {
            insert(insert_node, tree_root->left);   // If the LEFT of tree_root is not NULL, we recursively call insert on the left subtree.
        }
    }
    // If insert_node's value is greater than or equal to the current node's value, we go to the right subtree.
    if (insert_node->d() > tree_root->d()) {
        if (tree_root->right == NULL) {             // Put the insert_node on the right of tree_root if tree_root's right is NULL.
            tree_root->right = insert_node;
            insert_node->p = tree_root;             // Set the parent of the insert_node to the root node.
        } else {
            insert(insert_node, tree_root->right);  // If the RIGHT of tree_root is not NULL, we recursively call insert on the right subtree.
        }
    }
    return;
};

Node* find_max(Node * tree_root) {
    // find max of the tree or subtree
    // will be used in delete_node function: find maximum of right subtree
    // To find max of a subtree, we go right.
    if (tree_root == NULL)
        return NULL;
    if (tree_root->right == NULL)       // if there is nothing on the right, then tree_root is the max already
        return tree_root;
    return find_max(tree_root->right);  // else, keep looking for the max in the right subtree
}

void delete_node(int value, Node * & tree_root){
	//Your code here
    // If the tree is empty, we cannot delete anything. Return.
    if (tree_root == NULL) {
        return; // Tree is empty, nothing to delete
    }
    // If deleted value less than tree_root's value, then go into left-subtree and recursively call delete_node to find and delete the node holding 'value'.
    if (value < tree_root->d()) {
        delete_node(value, tree_root->left);  // Recursive Search and Delete in the left subtree
    // If deleted value greater than tree_root's value, then go into right-subtree and recursively call delete_node to find and delete the node holding 'value'.
    } else if (value > tree_root->d()) {
        delete_node(value, tree_root->right); // Recursive Search and Delete in the right subtree
    // else, we have found that the current node has same value as the value we want to delete.
    } else {
        // Case 1: No children (leaf node), then simply delete the node.
        if (tree_root->left == NULL && tree_root->right == NULL) {
            delete tree_root; // Delete the node
            tree_root = NULL; // Set the pointer to NULL
        }
        // Case 2A: One child in right subtree: after delete the node, we need to link right child to the parent of the deleted node.
        else if (tree_root->left == NULL && tree_root->right != NULL) {
            Node * oldNode = tree_root;
            tree_root = tree_root->right; // Replace tree_root with right child
            tree_root->p = oldNode->p;    // Update tree_root's parent to the parent of the old tree_root
            delete oldNode;               // Delete the old tree_root node
        }
        // Case 2B: One child in left subtree: similar to the case with right child, after we delete the node, 
        //          we need to link left child to the parent of the deleted node.
        else if (tree_root->left != NULL && tree_root->right == NULL) {
            Node * oldNode = tree_root;
            tree_root = tree_root->left; // Replace tree_root with left child
            tree_root->p = oldNode->p;   // Update tree_root's parent to the parent of the old tree_root
            delete oldNode;
        }
        // Case 3: Two children: after delete current tree_root node, we need to find a replacement node.
        //         Replacement node shall be the node with maximum value in the left-subtree.
        // Note: Can either find_min in the right subtree or find_max in the left subtree
        else {
            Node * maxNode_on_left = find_max(tree_root->left); // Find the maximum in the left subtree
            tree_root->setValue(maxNode_on_left->d());          // Replace the value with the max value
            delete_node(maxNode_on_left->d(), tree_root->left); // Recursive Delete the maximum node from the left subtree because we updated its value at tree_root
        }
    }
};

bool search(int value, Node * tree_root){
	//Your code here
    // Empty tree case
    if (tree_root == NULL) {
        cout << value << " not found in the tree." << endl;
        return false; // If tree is empty, return NULL i.e., the value can not be found in an empty tree.
    }

    // Non-empty tree case starts here
    // Case 1: If the value is less than the current node's value, keep the search in the left subtree.
    if (value < tree_root->d()) {
        return search(value, tree_root->left);
    }
    // Case 2: If the value is greater than the current node's value, keep the search in the right subtree.
    else if (value > tree_root->d()) {
        return search(value, tree_root->right);
    }
    // Case 3: We have found the value in the current node. Return.
    else {
        cout << value << " found in the tree." << endl;
        return true; // If the value matches the current node's value, return the current node.
    }
};

void printBinarySearchTree(Node* root) {
    if (root == NULL)
        return;
    printBinarySearchTree(root->left);
    std::cout << root->d() << " ";
    printBinarySearchTree(root->right);
}

bool isEmpty(Node* root) {
    if (root == NULL) {
        cout << "tree is empty." << endl;
        return true;
    } else {
        cout << "tree is not empty." << endl;
        return false;
    }
}


int main(int argc, const char * argv[])
{
    cout << "Starting program main!" << endl;

    // Part 1: Inserting nodes into the binary search tree
    cout << "\n\nPart 1: Inserting several values into the binary search tree" << endl;
    Node * t = NULL; // Initialize an empty binary search tree
    insert(new Node(15), t);
    insert(new Node(9), t);
    insert(new Node(0), t);
    insert(new Node(8), t);
    insert(new Node(4), t);
    insert(new Node(16), t);
    insert(new Node(2), t);
    insert(new Node(1), t);
    insert(new Node(11), t);
    insert(new Node(12), t);
    insert(new Node(20), t);
    printBinarySearchTree(t);

    // Part 2: Deleting nodes
    cout << "\n\nPart 2: Deleting several values in the binary search tree" << endl;
    cout << "Deleting node with value 0" << endl;
    delete_node(0, t);
    cout << "Deleting node with value 9" << endl;
    delete_node(9, t);
    printBinarySearchTree(t);

    // Part 3: Searching for a node
    cout << "\n\nPart 3: Searching for several values into the binary search tree" << endl;
    // isEmpty(t); // Check if the tree is empty
    search(16, t); // Try to search for 16 in the current tree
    // isEmpty(t);
    search(9, t); // Try to search for 9 in the current tree
    return 0;
}