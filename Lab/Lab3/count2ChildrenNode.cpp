#include<iostream>
#include<string>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

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
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value)
    {
        if(posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }

        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l-1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if(posFromRoot[l-1] == 'L')
            walker->pLeft = new Node(key, value);
        if(posFromRoot[l-1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // STUDENT ANSWER BEGIN
    int helperCountTwoChildrenNode(Node* root)
    {
        if (root == nullptr) 
        {
            return 0;
        }
        if (root->pLeft != nullptr && root->pRight != nullptr)
        {
            return 1 + helperCountTwoChildrenNode(root->pRight) + helperCountTwoChildrenNode(root->pLeft);
        }
        else 
        {
            return helperCountTwoChildrenNode(root->pLeft) + helperCountTwoChildrenNode(root->pRight);
        }
    }

    int countTwoChildrenNode()
    {
        return helperCountTwoChildrenNode(this->root);
    }
    // STUDENT ANSWER END
};