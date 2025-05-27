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
        return value;
    }
    void print() {
        std::cout << value << std::endl;
    }
};

void insert(Node * insert_node, Node * & tree_root){
	//Your code here
    // When tree_root is NULL, it means the tree is empty, and we can insert the new node as the root.
    if (tree_root == NULL) {
        tree_root = insert_node;
        return;
    }
    // If insert_node's value is less than the current node's value, we go to the left subtree.
    if (insert_node->d() < tree_root->d()) {
        if (tree_root->left == NULL) {
            tree_root->left = insert_node;
            insert_node->p = tree_root;
        } else {
            insert(insert_node, tree_root->left);
        }
    }
    // If insert_node's value is greater than or equal to the current node's value, we go to the right subtree.
    if (insert_node->d() > tree_root->d()) {
        if (tree_root->right == nullptr) {
            tree_root->right = insert_node;
            insert_node->p = tree_root;
        } else {
            insert(insert_node, tree_root->right);
        }
    }
    return;
};

void printBinarySearchTree(Node* root) {
    if (root == nullptr)
        return;

    printBinarySearchTree(root->left);
    std::cout << root->d() << " ";
    printBinarySearchTree(root->right);
}


int main(int argc, const char * argv[])
{
    cout << "Starting program main!" << endl;
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
    return 0;
}

// void delete_node(int value, Node *tree_root){
// 	//Your code here
// };

// Node* search(int value, Node *tree_root){
// 	//Your code here
// };