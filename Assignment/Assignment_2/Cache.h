#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class Factor {
public:
    Elem *elem;
    int freq;
    int peri;
    Factor() : elem(nullptr), freq(0), peri(0) {}
    Factor(int f, int r) : elem(nullptr), freq(f), peri(r) {}
    Factor(int addr, Data *d, bool s) {
        elem = new Elem(addr, d, s);
        freq = 0;
        peri = 0;
    }
    ~Factor() {}
};

class ReplacementPolicy {
public:
    Factor **heap;
    Factor **prime;
    int size;

    ReplacementPolicy() {
        heap = new Factor* [MAXSIZE];
        prime = new Factor* [MAXSIZE];
        size = 0;
    }
    ~ReplacementPolicy() {}

    void insertPri(Factor ftr) {
        prime[size - 1] = new Factor(ftr);
    }
    void setPri(int addr, Data *d) {
        for (int i = 0; i < size; ++i) {
            if (prime[i] != nullptr && prime[i]->elem->addr == addr) {
                Factor f(addr, d, false);
                prime[i] = new Factor(f);
            }
        }
    }
    void swapPri(int addr, Factor ftr) {
        for (int i = 0; i < size; ++i) {
            if (prime[i] != nullptr && prime[i]->elem->addr == addr) prime[i] = new Factor(ftr);
        }
    }
    void updatePeriod() {
        for (int i = 0; i < size; ++i) ++heap[i]->peri;
    }
    void printPri() {
        for (int i = 0; i < size; ++i) {
            prime[i]->elem->print();
        }
    }
    bool findFac(int addr){
        for (int i = 0; i < size; i++) {
            if (heap[i]->elem->addr == addr) return true;
        }
        return false;
    }
    void printHashTable(){
        Factor* ftr[size];
        for (int i = 0; i < size; ++i) ftr[i] = nullptr;
        for (int i = 0; i < size; ++i) {
            int id = prime[i]->elem->addr % MAXSIZE;
            for (int j = 0; j <= size; ++j){
                if (ftr[id] == nullptr){
                    ftr[id] = new Factor(*prime[i]);
                    break;
                }
                else {
                    ++id;
                    if (id >= size) id = 0;
                }
            }            
        }
        for (int i = 0; i < size; ++i) {
            ftr[i]->elem->print();
        }
        for (int i = 0; i < size; ++i) {
            delete ftr[i];
        }
    }

    virtual Factor* find(int) = 0;
    virtual Elem* insert(Factor*) = 0;
    virtual Elem* write(int, Factor*) = 0;
    virtual void print() = 0;
};

//----------1-implement idOfHeap----------
int parentOf(int id) {
    return (id - 1) / 2;
} 

int leftChildOf(int id) {
    return 2 * id + 1;
}

int rightChildOf(int id) {
    return 2 * id + 2;
}
//----------0-implement idOfHeap----------

class MFU : public ReplacementPolicy {
    Factor* find(int addr) {
        for (int i = 0; i < size; ++i) {
            if (heap[i]->elem->addr == addr) {
                Factor* f = new Factor(*heap[i]);
                updateFreq(i);
                return f;
            }
        } 
        return nullptr;
    }

    void reHeapDown(int i) {
        int leftChild = leftChildOf(i);
        int rightChild = rightChildOf(i); 
        int larger = i;

	    if (leftChild < size && heap[leftChild]->freq >= heap[i]->freq) {
	    	larger = leftChild;
	    }
	    if (rightChild < size && heap[rightChild]->freq >= heap[larger]->freq) {
	    	larger = rightChild;
	    }

	    if (larger != i) {
	    	swap(heap[larger], heap[i]);
	    	reHeapDown(larger);
	    }
    }   
    Elem* deleteFac(int i) {
        Elem* ftrToDel = heap[i]->elem;
        heap[i] = heap[size - 1];
        --size;
        reHeapDown(i);
        return ftrToDel;
    }
    Elem* insert(Factor* ftr) {
        Elem* facFull = nullptr;
        if (size == MAXSIZE) {
            facFull = deleteFac(0);
        }

        size++;
        int i = size - 1;
        heap[i] = ftr;
        
        while (i != 0 && heap[parentOf(i)]->freq < heap[i]->freq)
        {
            swap(heap[i], heap[parentOf(i)]);
            i = parentOf(i);
        }
        return facFull;
    }

    void updateFreq(int id){
        Factor* ftr = new Factor(*heap[id]);
        ++ftr->freq;
        deleteFac(id);
        insert(ftr);
    }
    Elem* write(int addr, Factor* ftr) {
        Elem* t = nullptr;
        for (int i = 0; i < size; ++i) {
            if (heap[i]->elem->addr == addr) {
                heap[i]->elem = ftr->elem;
                updateFreq(i);
                setPri(addr, ftr->elem->data);
                return nullptr;
            }
        }
        Factor* f = new Factor(*ftr);
        t = insert(ftr);
        if(t == nullptr) insertPri(*f);
        else swapPri(t->addr, *f);
        return t;
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            heap[size - i - 1]->elem->print();
        }
    }
};

class LFU : public ReplacementPolicy {
    Factor *find(int address) {
        for (int i = 0; i < size; i++) {
            if (heap[i]->elem->addr == address) {
                Factor* f = new Factor(*heap[i]);
                updateFreq(i);
                return f;
            }
        }
        return nullptr;
    }
    void reHeapDown(int i) {
        int leftChild = leftChildOf(i);
        int rightChild = rightChildOf(i); 
        int smaller = i;
	   
	    if (rightChild < size && heap[rightChild]->freq <= heap[i]->freq) {
	    	smaller = rightChild;
	    }
	    if (leftChild < size && heap[leftChild]->freq <= heap[smaller]->freq) {
	    	smaller = leftChild;
	    }
	    
	    if (smaller != i) {
	    	swap(heap[smaller], heap[i]);
	    	reHeapDown(smaller);
	    }
    }   
    Elem* deleteFac(int i) {
        Elem* ftrToDel = heap[i]->elem;
        heap[i] = heap[size - 1];
        --size;
        reHeapDown(i);
        return ftrToDel;
    }
    Elem* insert(Factor* ftr) {
        Elem* facFull = nullptr;
        if (size == MAXSIZE) {
            facFull = deleteFac(0);
        }

        size++;
        int i = size - 1;
        heap[i] = ftr;
        
        while (i != 0 && heap[parentOf(i)]->freq > heap[i]->freq)
        {
            swap(heap[i], heap[parentOf(i)]);
            i = parentOf(i);
        }
        return facFull;
    }

    void updateFreq(int id){
        Factor* ftr = new Factor(*heap[id]);
        ++ftr->freq;
        deleteFac(id);
        insert(ftr);
    }
    Elem* write(int addr, Factor* ftr) {
        Elem* t = nullptr;
        for (int i = 0; i < size; ++i) {
            if (heap[i]->elem->addr == addr) {
                heap[i]->elem = ftr->elem;
                updateFreq(i);
                setPri(addr, ftr->elem->data);
                return nullptr;
            }
        }
        Factor* f = new Factor(*ftr);
        t = insert(ftr);
        if (t == nullptr) insertPri(*f);
        else swapPri(t->addr, *f);
        return t;
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            heap[i]->elem->print();
        }
    }
};
class MFRU: public ReplacementPolicy {
    void reHeapDown(int i)
    {
        int leftChild = leftChildOf(i);
        int rightChild = rightChildOf(i);
        int larger = i;
        if ((leftChild < size && heap[leftChild]->freq > heap[i]->freq)||(leftChild < size && heap[leftChild]->freq == heap[i]->freq && heap[leftChild]->peri <= heap[i]->peri))
            larger = leftChild;
        if ((rightChild < size && heap[rightChild]->freq > heap[larger]->freq)||(rightChild < size && heap[rightChild]->freq == heap[i]->freq && heap[rightChild]->peri <= heap[i]->peri))
            larger = rightChild;
        if (larger != i)
        {
            swap(heap[i], heap[larger]);
            reHeapDown(larger);
        }
    }
    Elem* deleteFac(int i) {
        Elem* ftrToDel = heap[i]->elem;
        heap[i] = heap[size - 1];
        --size;
        reHeapDown(i);
        return ftrToDel;
    }

    Elem* insert(Factor* ftr) {
        Elem* facFull = nullptr;
        if (size == MAXSIZE) {
            facFull = deleteFac(0);
        }

        size++;
        int i = size - 1;
        heap[i] = ftr;
        
        while ((i != 0 && heap[parentOf(i)]->freq < heap[i]->freq ) ||(i != 0 && heap[parentOf(i)]->freq == heap[i]->freq && heap[parentOf(i)]->peri > heap[i]->peri))
        {
            swap(heap[i], heap[parentOf(i)]);
            i = parentOf(i);
        }
        return facFull;
    }

    Factor* find(int addr) {
        for (int i = 0; i < size; ++i) {
            if (heap[i]->elem->addr == addr) {
                Factor* f = new Factor(*heap[i]);
                updateFreq(i);
                return f;
            }
        } 
        return nullptr;
    }

    void updateFreq(int id){
        Factor* ftr = new Factor(*heap[id]);
        ++ftr->freq;
        deleteFac(id);
        insert(ftr);
    }
    Elem* write(int addr, Factor* ftr) {
        Elem* t = nullptr;
        for (int i = 0; i < size; ++i) {
            if (heap[i]->elem->addr == addr) {
                heap[i]->elem = ftr->elem;
                updateFreq(i);
                setPri(addr, ftr->elem->data);
                return nullptr;
            }
        }
        Factor* f = new Factor(*ftr);
        t = insert(ftr);
        if(t == nullptr) insertPri(*f);
        else swapPri(t->addr, *f);
        return t;
    }
    void print() {
        Factor *f[size];
        for (int i = 0; i < size; i++) {
            f[i] = new Factor(*heap[i]);
        }
        for (int j = 0; j < size; j++)
        for (int i = 1; i < size; i++) {
            if ((f[i - 1]->freq < f[i]->freq) || (f[i]->freq == f[i - 1]->freq && f[i - 1]->peri > f[i]->peri))
            swap(f[i], f[i - 1]);
        }
        for (int i = 0; i < size; i++) {
            f[i]->elem->print();
        }
        for (int i = 0; i < size; i++) {
            delete f[i];
        }

    }
};

class LFRU: public ReplacementPolicy {
    void reHeapDown(int i)
    {
        int leftChild = leftChildOf(i);
        int rightChild = rightChildOf(i);
        int larger = i;
        if ((rightChild < size && heap[rightChild]->freq < heap[i]->freq )||(rightChild < size && heap[rightChild]->freq == heap[i]->freq && heap[leftChild]->peri >= heap[i]->peri ))
            larger = rightChild;
        if ((leftChild < size && heap[leftChild]->freq < heap[larger]->freq)||(leftChild < size && heap[leftChild]->freq == heap[i]->freq && heap[leftChild]->peri >= heap[i]->peri ))
            larger = leftChild;
        if (larger != i)
        {
            swap(heap[i], heap[larger]);
            reHeapDown(larger);
        }
    }
    Factor* find(int addr) {
        for (int i = 0; i < size; ++i) {
            if (heap[i]->elem->addr == addr) {
                Factor* f = new Factor(*heap[i]);
                updateFreq(i);
                return f;
            }
        } 
        return nullptr;
    }

    Elem* deleteFac(int i) {
        Elem *ftrToDel = heap[i]->elem;
        heap[i] = heap[size-1];
        --size;
        reHeapDown(i);
        
        return ftrToDel;
    }
    Elem* insert(Factor* ftr) {
        Elem* facFull = nullptr;
        if (size == MAXSIZE) {
            facFull = deleteFac(0);
        }

        size++;
        int i = size - 1;
        heap[i] = ftr;
        
        while ((i != 0 && heap[parentOf(i)]->freq > heap[i]->freq ) ||(i != 0 && heap[parentOf(i)]->freq == heap[i]->freq && heap[parentOf(i)]->peri < heap[i]->peri))
        {
            swap(heap[i], heap[parentOf(i)]);
            i = parentOf(i);
        }
        return facFull;
    }

    void updateFreq(int id){
        Factor* ftr = new Factor(*heap[id]);
        ++ftr->freq;
        ftr->peri = 0;
        deleteFac(id);
        insert(ftr);
    }   
    Elem* write(int addr, Factor* ftr) {
        Elem* t = nullptr;
        for (int i = 0; i < size; ++i) {
            if (heap[i]->elem->addr == addr) {
                heap[i]->elem = ftr->elem;
                updateFreq(i);
                setPri(addr, ftr->elem->data);
                return nullptr;
            }
        }
        Factor* f = new Factor(*ftr);
        t = insert(ftr);
        if (t == nullptr) insertPri(*f);
        else swapPri(t->addr, *f);
        return t;
    }
    void print() {
        Factor *f[size];
        for (int i = 0; i < size; i++) {
            f[i] = new Factor(*heap[i]);
        }
        for (int j = 0; j < size; j++)
        for (int i = 1; i < size; i++) {
            if ((f[i - 1]->freq > f[i]->freq) || (f[i]->freq == f[i - 1]->freq && f[i - 1]->peri < f[i]->peri))
            swap(f[i], f[i - 1]);
        }
        for (int i = 0; i < size; i++) {
            f[i]->elem->print();
        }
        for (int i = 0; i < size; i++) {
            delete f[i];
        }
    }
};

//----------1-inplement BST : SearchEngine----------

class Node {
public:
    Factor factor;
    Node* left = nullptr;
    Node* right = nullptr;
};

class SearchEngine {
public:
    virtual void print() = 0;
    virtual void insert(Factor) = 0;
    virtual void remove(int) = 0;
    virtual void set(int, Factor) = 0;
};

class BST : public SearchEngine
{
    Node *makeEmpty(Node *root) {
        if (root == nullptr) return nullptr;
        makeEmpty(root->left);
        makeEmpty(root->right);
        delete root;
        return nullptr;
    }

    Node *insert(Factor ftr, Node *root) {
        if (root == nullptr) {
            root = new Node;
            root->factor = ftr;
            root->left = root->right = nullptr;
        }
        else if (ftr.elem->addr < root->factor.elem->addr) root->left = insert(ftr, root->left);
        else if (ftr.elem->addr > root->factor.elem->addr) root->right = insert(ftr, root->right);
        return root;
    }

    Node *findMin(Node *root) {
        if (root == nullptr) return nullptr;
        else if (root->left == nullptr) return root;
        else return findMin(root->left);
    }

    Node *findMaftr(Node *root) {
        if (root == nullptr) return nullptr;
        else if (root->right == nullptr) return root;
        else return findMaftr(root->right);
    }

    Node *remove(int addr, Node *root) {
        Node *temp;
        if (root == nullptr) return nullptr;
        else if (addr < root->factor.elem->addr) root->left = remove(addr, root->left);
        else if (addr > root->factor.elem->addr) root->right = remove(addr, root->right);
        else if (root->left && root->right) {
            temp = findMin(root->right);
            root->factor = temp->factor;
            root->right = remove(root->factor.elem->addr, root->right);
        }
        else {
            temp = root;
            if (root->left == nullptr) root = root->right;
            else if (root->right == nullptr) root = root->left;
            delete temp;
        }
        return root;
    }

    Node *find(Node *root, int addr) {
        if (root == nullptr) return nullptr;
        else if (addr < root->factor.elem->addr) return find(root->left, addr);
        else if (addr > root->factor.elem->addr) return find(root->right, addr);
        else return root;
    }

public:
    Node *root;
    BST() {
        root = nullptr;
    }
    ~BST() {
        root = makeEmpty(root);
    }

    void inorder(Node *root) {
        if (root == nullptr) return;
        inorder(root->left);
        root->factor.elem->print();
        inorder(root->right);
    }
    void preorder(Node *root) {
        if (root == nullptr) return;
        root->factor.elem->print();
        preorder(root->left);
        preorder(root->right);
    }
    void insert(Factor ftr) {
        root = insert(ftr, root);
    }

    void remove(int ftr) {
        root = remove(ftr, root);
    }

    void print() {
        cout<<"Print BST in inorder:\n";
        inorder(root);
        cout<<"Print BST in preorder:\n";
        preorder(root);
    }

    void set(int addr, Factor ftr) {
        Node* temp = find(root, addr);
        temp->factor= ftr;
    }
};
//----------0-inplement BST : SearchEngine----------
#endif