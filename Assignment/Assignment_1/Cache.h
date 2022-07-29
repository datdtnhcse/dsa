#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class Node {
    public:
    int address;
    int index;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int addr, int id) {
        address = addr;
        index = id;
    }
};

class BSTree {
    public:
    Node* root = nullptr;
    BSTree();
    ~BSTree() {
        Node* r00t = root;
        deleteTree(r00t);
    }
    Node* addNode(int addr, int index, Node* node);
    Node* searchNode(int addr, Node* node);
    Node* minNode(Node* root);
    Node* deleteNode(int addr, Node* node);
    void minusIndexOfNode(Node* r00t);
    void printInorder(Node* r00t, Elem** arr);
    void printPreorder(Node* r00t, Elem** arr);
    void deleteTree(Node* r00t);
};

class Cache {
        Elem** arr;
        int p;
        BSTree Tree;
	public:
    Cache(int s) {
        arr = new Elem*[s];
        p = 0;
    }
    ~Cache() {
        delete[] arr;
    }
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();
};

Node* BSTree::addNode(int addr, int index, Node* node) {
    if (node == nullptr) {
        return new Node(addr, index);
    }
    if (addr < node->address) node->left = addNode(addr, index, node->left);
    if (addr > node->address) node->right = addNode(addr, index, node->right);
    return node;
}

Node* BSTree::searchNode(int addr, Node* node) {
    if (node == nullptr || node->address == addr) return node;
    if (node->address < addr) return searchNode(addr, node->right);
    return searchNode(addr, node->left);
}

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

void BSTree::minusIndexOfNode(Node* r00t) {
    if (r00t == nullptr) return;
    minusIndexOfNode(r00t->left);
    r00t->index--;
    minusIndexOfNode(r00t->right);
}

void BSTree::printInorder(Node* r00t, Elem** arr) {
    if (r00t == nullptr) return;
    printInorder(r00t->left, arr);
    arr[r00t->index]->print();
    printInorder(r00t->right, arr);
}

void BSTree::printPreorder(Node* r00t, Elem** arr) {
    if (r00t == nullptr) return;
    arr[r00t->index]->print();
    printPreorder(r00t->left, arr);
    printPreorder(r00t->right, arr);
}

void BSTree::deleteTree(Node* r00t) {
    if (r00t == nullptr) return;
    deleteTree(r00t->left);
    deleteTree(r00t->right);
    delete r00t;
}

BSTree::BSTree(){}
#endif