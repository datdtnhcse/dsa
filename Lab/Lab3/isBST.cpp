#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // STUDENT ANSWER BEGIN 

    int countNode(Node* root) {
        if (root == nullptr) return 0;
        return 1 + countNode(root->pLeft) + countNode(root->pRight);
    }

    void helper(Node* root, int* arr, int &i) {
        if (root == nullptr) return;
        helper(root->pLeft, arr, i);
        arr[i++] = root->value;
        helper(root->pRight, arr, i);
    }

    bool isBST() {
        int size = countNode(root);
        int* arr = new int[size];
        int i = 0;
        helper(root, arr, i);
        for (int k = 1; k < size - 1; ++k) {
            if (arr[k] < arr[k - 1]) return false;
        }
        return true;
    
    }

    // STUDENT ANSWER END
};