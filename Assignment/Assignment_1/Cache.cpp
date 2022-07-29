#include "main.h"
#include "Cache.h"

Data* Cache::read(int addr) {
    Node* foundNode = Tree.searchNode(addr, Tree.root); // // search in BSTree & return index

    if (foundNode == nullptr) return nullptr;
    

    return arr[foundNode->index]->data; // get elem from *arr
}

Elem* Cache::put(int addr, Data* cont) {
    if (p < MAXSIZE) { // normal
        Elem* newElem = new Elem(addr, cont, true); // create new Elem to put
        arr[p] = newElem; // put to *arr

        Tree.root = Tree.addNode(addr, p, Tree.root); // add to Tree
            
        ++p;
        return nullptr;
    }
    else { // LIFO and FIFO
        if (addr%2 == 0) { // FIFO
            int ad = arr[0]->addr; // get [0] elem's address
                
            Node* r00t = Tree.root;
            Tree.deleteNode(ad, r00t); // delete [0] in Tree

            Elem* delElem = arr[0]; // delete [0] in *arr
            for (int i = 0; i < p-1; i++) { 
                arr[i] = arr[i+1];
            }
            Elem* newElem = new Elem(addr, cont, true); // create new Elem to put
            arr[p-1] = newElem; // put to *arr

            r00t = Tree.root;
            Tree.minusIndexOfNode(r00t); // -- index of all Tree's node

            r00t = Tree.root;
            Tree.addNode(addr, p-1, r00t); // put to Tree
            
            return delElem; // return deleted Elem
        }
        else { // LIFO
            int ad = arr[p-1]->addr; // get [0] elem's address
                
            Node* r00t = Tree.root;
            Tree.deleteNode(ad, r00t); // delete [p-1] in Tree

            Elem* delElem = arr[p-1]; // delete [p-1] in *arr
            Elem* newElem = new Elem(addr, cont, true); // create new Elem to put
            arr[p-1] = newElem; // put to *arr

            r00t = Tree.root;
            Tree.addNode(addr, p-1, r00t); // put to Tree

            return delElem; // return deleted Elem
        } 
    }
}
Elem* Cache::write(int addr, Data* cont) {
    int ad = addr;
    Node* r00t = Tree.root;
    Node* foundNode = Tree.searchNode(ad, r00t); // find node in Tree
    
    if (foundNode == nullptr) { // not existed in Tree
        Elem* outElem = put(addr, cont); // get out Elem*
        arr[p-1]->sync = false; // set sync false
        return outElem; 
    } 
    else { // existed in Tree
        arr[foundNode->index]->data = cont;
        arr[foundNode->index]->sync = false;
        return nullptr;
    }
}
void Cache::print() {
	for (int i = p-1; i >= 0; i--)
        arr[i]->print();
}
void Cache::preOrder() {
	Node* r00t = Tree.root;
    Tree.printPreorder(r00t, arr);
}
void Cache::inOrder() {
	Node* r00t = Tree.root;
    Tree.printInorder(r00t, arr);
}