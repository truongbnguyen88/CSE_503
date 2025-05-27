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


int main(int argc, const char * argv[])
{
    
}

function insert(Node *insert_node, Node *tree_root){
	//Your code here
}

function delete_node(int value, Node *tree_root){
	//Your code here
}

function search(int value, Node *tree_root){
	//Your code here
}