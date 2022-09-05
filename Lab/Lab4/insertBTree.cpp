#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class K, class D, int M> // K: key, D: data, M: degree of BTree
class BTree {
    /// Convention: Left sub-tree < Root's key <= Right sub-tree

public:
    class Entry;

    class Node;

private:
    Node *root;

public:
    BTree() : root(0) {};

    ~BTree() {}
    ///////////////////////////////////////////////////
    ///             CLASS `Entry`                   ///
    ///////////////////////////////////////////////////
public:
    class Entry {
    private:
        K key;
        D data;
        Node *rightPtr;

        friend class BTree<K, D, M>;

    public:
        Entry(K key = K{}, D value = D{}) : key(key), data(value), rightPtr(0) {}
        ~Entry() {}
        string toString() {
            stringstream ss;
            ss << "<"
                   << this->key << ","
                   << this->data
                   << ">";
            return ss.str();
        }
    };

    ///////////////////////////////////////////////////
    ///             CLASS `Node`                    ///
    ///////////////////////////////////////////////////
public:
    class Node {
    private:
        Node *firstPtr;
        int numEntries;
        Entry entries[M - 1];

        friend class BTree<K, D, M>;

    public:
        Node() : firstPtr(0), numEntries(0) {};

        ~Node() { }
        string toString() {
            stringstream ss;
            // Fill your own code here
            return ss.str();
        }
        bool isFull() {
            return (numEntries >= M - 1);
        }
    };

    /////////////////////////////////////////////////////////////
    ///         CLASS `BTree`: method implementation          ///
    /////////////////////////////////////////////////////////////
public:
    /// toStringPreOrder()
    string toStringPreOrder();
    /// BEGIN STUDENT CODE
    void insert(const K& key, const D& data) {
        
    }
    /// END STUDENT CODE
};