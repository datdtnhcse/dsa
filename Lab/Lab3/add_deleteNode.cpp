#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    Node* addNode(T value, Node* r00t) {
        if (r00t == nullptr) return new Node(value);
        if (value > r00t->value) r00t->pRight = addNode(value, r00t->pRight);
        else r00t->pLeft = addNode(value, r00t->pLeft);
        return r00t;
    }

    void add(T value) {
        root = addNode(value, root);
    }
   
   Node* minNode(Node* r00t) {
        if (r00t == nullptr) return nullptr;
        if (r00t->pLeft == nullptr) return r00t;
        return minNode(r00t->pLeft);    
   }

   Node* deleteNo(T value, Node* node) {
    Node* tmp;
    if (node == nullptr) return nullptr;
    else if(value < node->value) node->pLeft = deleteNo(value, node->pLeft);
    else if(value > node->value) node->pRight = deleteNo(value, node->pRight);
    else if(node->pLeft && node->pRight) {
        tmp = minNode(node->pRight);
        node->value = tmp->value;
        node->pRight = deleteNo(node->value, node->pRight);
    }
    else {
        tmp = node;
        if (node->pLeft == nullptr) node = node->pRight;
        else if(node->pRight == nullptr) node = node->pLeft;
        delete tmp;
    }
    return node;
}

    void deleteNode(T value) {
        root = deleteNo(value, root);
    }
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }
    
    string inOrder(){
        return inOrderRec(this->root);
    }
    
    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};


/*
Node* BSTree::minNode(Node* node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;
    return minNode(node->left);
}

Node* BSTree::deleteNode(int addr, Node* node) {
    Node* tmp;
    if (node == nullptr) return nullptr;
    else if(addr < node->address) node->left = deleteNode(addr, node->left);
    else if(addr > node->address) node->right = deleteNode(addr, node->right);
    else if(node->left && node->right) {
        tmp = minNode(node->right);
        node->address = tmp->address;
        node->right = deleteNode(node->address, node->right);
    }
    else {
        tmp = node;
        if (node->left == nullptr) node = node->right;
        else if(node->right == nullptr) node = node->left;
        delete tmp;
    }
    return node;
}
*/