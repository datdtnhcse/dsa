#include<iostream>

using namespace std;

template <class T>
class SLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;
public:
    SLinkedList() : head(NULL), tail(NULL), count(0){};
    ~SLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString();
    SLinkedList(const SLinkedList &list)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;
    public:
        Node()
        {
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator
    {
    private:
        SLinkedList<T> *pList;
        Node *current;
        int index; // corresponding with current node
    public:
        Iterator(SLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);

        void remove();
    };
};

class Polynomial;
class Term {
private:
    double coeff;   
    int exp;
    friend class Polynomial;
public:
    Term(double coeff = 0.0, int exp = 0) {
        this->coeff = coeff;
        this->exp = exp;
    }
    bool operator==(const Term& rhs) const {
        return this->coeff == rhs.coeff && this->exp == rhs.exp;
    }
    friend ostream & operator<<(ostream &os, const Term& term) {
        cout << endl;
        cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
        return os;
    }
};
class Polynomial {
private:
    SLinkedList<Term>* terms;
public:
    Polynomial() {
        this->terms = new SLinkedList<Term>();
    }
    ~Polynomial() {
        this->terms->clear();
    }
    void insertTerm(const Term& term);
    void insertTerm(double coeff, int exp);
    void print() {
        SLinkedList<Term>::Iterator it(nullptr, 1);
        cout << "[";
        for (it = this->terms->begin(); it != this->terms->end(); it++) {
            cout << (*it);
        }
        cout << endl << "]";
    }
};

/////////////////////////////////
/////////////Prob2///////////////
/////////////////////////////////

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
    /*
        Constructor of iterator
        * Set pList to pList
        * begin = true: 
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        * begin = false: 
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */
    this->pList = pList;
    if (begin) {
        if (pList != nullptr) {
            this->index = 0;
            this->current = pList->head;
        } else {
            this->index = -1;
            this->current = nullptr;
        } 
    } else {
            this->current = nullptr;
            if (pList != nullptr) this->index = pList->count;
            else this->index = 0;
    }
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
    /*
        Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
    */
    if (current == nullptr) throw std::out_of_range("Segmentation fault!");
    if (current == pList->head) {
        pList->head = pList->head->next;
        pList->count--;
        delete current; 
        current = nullptr; 
        index = -1;
    } else {
        Node* temp = pList->head;
        while (temp->next != current) temp = temp->next; 
        Node* nodeDel = current;
        temp->next = current->next; 
        current = temp;
        delete nodeDel;
        pList->count--;
        index--;
    }
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (current == nullptr) throw std::out_of_range("Segmentation fault!");
    current->data = e;
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
   if (current == nullptr) throw std::out_of_range("Segmentation fault!");
   return current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    /*
        Operator not equals
        * Returns true if two iterators points the same node and index
    */
   return ((pList != iterator.pList) || (index != iterator.index));
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    if  (current == nullptr) throw std::out_of_range("Segmentation failed!");
    
    if (pList == nullptr) {
        current = nullptr;
        index = -1;
        return *this;
    }

    if (index == -1) {
        current = pList->head;
    } else {
        current = current->next;
    }
    index++; 
    return *this;
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    Iterator temp = *this;
    ++(*this);
    return temp;
}

/////////////////////////////////
/////////////Prob1///////////////
/////////////////////////////////

void Polynomial::insertTerm(const Term& term) {
    if (term.coeff == 0) return;
    auto it = terms->begin();
    int id = 0;
    while (it != terms->end() && term.exp < (*it).exp) {
        ++it;
        ++id;
    }
    if (!(it != terms->end())) terms->add(term);
    else if (term.exp == (*it).exp) {
        (*it).coeff += term.coeff;
        if ((*it).coeff == 0) terms->removeAt(id);
    }
    else if (term.exp > (*it).exp) {
        terms->add(id, term);
    }
}

void Polynomial::insertTerm(double coeff, int exp) {
    auto term = Term(coeff, exp);
    insertTerm(term);
}

/////////////////////////////////
/////////////Prob3///////////////
/////////////////////////////////

template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    Node* newNode = new Node {e, nullptr};
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        count++;
        newNode = nullptr;
        return;
    }
    tail->next = newNode;
    tail = newNode;
    count++;
    newNode = nullptr;
    return;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    Node* temp = head;
    Node* newNode = new Node {e, nullptr};
    
    if (index == 0) {
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            count++;
            return;
        }
        newNode->next = head;
        head = newNode;
        newNode = nullptr;
        count++; 
        return;
    }

    while(1) {
        if (index-1 == 0) {
            newNode->next = temp->next;
            temp->next = newNode;
            if (newNode->next == nullptr) tail = newNode;
            newNode = nullptr;
            count++;
            return;
        }
        temp = temp->next;
        index--;
    }
}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return count;
}

/////////////////////////////////
/////////////Prob4///////////////
/////////////////////////////////


template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= count) throw std::out_of_range("Segmentation fault!");
    Node* temp = head;
    while (1) {
        if (!index) return temp->data;
        temp = temp->next;
        index--;
    }
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= count) throw std::out_of_range("Segmentation fault!");
    Node* temp = head;
    while (1) {
        if (!index) {
            temp->data = e;
            return;
        }
        temp = temp->next;
        index--;
    }
}

template<class T>
bool SLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return (head == nullptr);
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    int index = 0;
    Node* temp = head;
    while (1) {
        if (temp == nullptr) return -1;
        if (temp->data == item) return index;
        temp = temp->next;
        index++;
    }
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    return (indexOf(item) != -1);
}

/////////////////////////////////
/////////////Prob5///////////////
/////////////////////////////////

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if (index == 0) {
        if (count == 1) {
            Node* temp = head;
            head = nullptr;
            tail = nullptr;
            count--;
            T ret = temp->data;
            delete temp;
            return ret;
        } else {
            Node* temp = head;
            head = head->next;
            T ret = temp->data;
            delete temp;
            count--;
            return ret;
        }

    }
    Node* temp = head;
    int id = index;
    while (1) {
        if (index == 1) {
            int ret = temp->next->data;
            if (id == count-1) {
                Node* newNode = tail;
                tail = temp;
                count--;
                delete newNode; 
                return ret;
            }
            Node* newNode = temp->next;
            temp->next = temp->next->next;
            this->count--;
            delete newNode;
            return ret;
        }
        temp = temp->next;
        index--;
    }
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    int index = this->indexOf(item);
    if (index != -1) {
        this->removeAt(index);
        return 1;
    } else return 0;
}

template<class T>
void SLinkedList<T>::clear(){
    /* Remove all elements in list */
    while (1) {
        if (count == 0) return;
        if (count == 1) {
            Node* temp = head;
            head = nullptr;
            tail = nullptr;
            count--;
            delete temp;
        }
        else {
            Node* temp = head;
            head = head->next;
            count--;
            delete temp;
        }
    }
}

