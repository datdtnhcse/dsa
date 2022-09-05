#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    int getBalanceValue(Node* root){
        return getHeightRec(root->pLeft) - getHeightRec(root->pRight); 
    }

    Node* leftRotate(Node* root){
        Node* rightTree = root->pRight;
        root->pRight = rightTree->pLeft;
        rightTree->pLeft = root;

        int rootBalance = getBalanceValue(rightTree);
        if (rootBalance == -1){
            root->balance = LH;
        }
        else if (rootBalance == 0){
            root->balance = EH;
        }
        else {
            root->balance = RH;
        }
        int rightTreeBalance = getBalanceValue(root);
        if (rightTreeBalance == -1){
            rightTree->balance = LH;
        }
        else if (rightTreeBalance == 0){
            rightTree->balance = EH;
        }
        else {
            rightTree->balance = RH;
        }
        return rightTree;
    }

    Node* rightRotate(Node* root){
        Node* leftTree = root->pLeft;
        root->pLeft = leftTree->pRight;
        leftTree->pRight = root;

        int rootBalance = getBalanceValue(leftTree);
        if (rootBalance == -1){
            root->balance = LH;
        }
        else if (rootBalance == 0){
            root->balance = EH;
        }
        else {
            root->balance = RH;
        }
        int leftTreeBalance = getBalanceValue(root);
        if (leftTreeBalance == -1){
            leftTree->balance = LH;
        }
        else if (leftTreeBalance == 0){
            leftTree->balance = EH;
        }
        else {
            leftTree->balance = RH;
        }
        return leftTree;
    }

    Node* insertHelp(Node* &root, const T &value){
        if (root == NULL){
            return new Node(value);
        }
        if (value < root->data){
            root->pLeft = insertHelp(root->pLeft,value);
        }
        else {
            root->pRight = insertHelp(root->pRight,value);
        }
        int balance = getBalanceValue(root);
        if (balance > 1){
            //left of left
            if (root->pLeft->data > value){
                return rightRotate(root);
            }
            //right of left
            else {
                root->pLeft = leftRotate(root->pLeft);
                return rightRotate(root);
            }
        }
        if (balance < -1){
            //right of right
            if (root->pRight->data <= value){
                return leftRotate(root);
            }
            else {
                root->pRight = rightRotate(root->pRight);
                return leftRotate(root);
            }
        }
        return root;
    }

    void insert(const T &value){
        root = insertHelp(root, value);
    }

    void printInordeerHelper(Node* node)
    {
        if (node == nullptr) return;
        printInordeerHelper(node->pLeft);
        cout << node->data << ' ';
        printInordeerHelper(node->pRight);
    }

    void printInorder()
    {
        printInordeerHelper(root);
    }

    bool searchHelper(Node* node, const T &value)
    {
        if (node == nullptr) return 0;
        if (node->data == value)
        {
            return 1;
        }
        if (node->data < value) return searchHelper(node->pRight, value);
        if (node->data > value) return searchHelper(node->pLeft, value);
    }

    bool search(const T &value){
        return searchHelper(root, value);
    }

    void clear() {}

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };


    
};