#include<iostream>
using namespace std;

typedef int Elem;
class SNode {					// circularly linked list node
    private:
        Elem elem;					// linked list element value
        SNode* next;				// next item in the list

    friend class SLinkedList;			// provide CircleList access
};

class SLinkedList {			// a singly linked list of Elems
    public:
        SLinkedList();			    // empty list constructor
        ~SLinkedList();			// destructor
        bool empty() const;				// is list empty?
        const Elem& front() const;		// get front element
        void addFront(const Elem& e);		// add to the front of list
        void removeFront();				// remove front item list
        int sumRec();
        void printReverseRec(SNode* header);
        void printRec();
        bool containsRec(int n, SNode* header);
        int sizeRec();
    private:
        SNode* head;				// pointer to the head of list
        int _sizeRec(SNode* node);
        int _sumRec(SNode* node);
        void _printRec(SNode* header);
        void _printReverseRec(SNode* header);
};

SLinkedList::SLinkedList()			// constructor
    : head(NULL) { }

SLinkedList::~SLinkedList()			// destructor
    { while (!empty()) removeFront(); }

bool SLinkedList::empty() const			// is list empty?
    { return head == NULL; }

const Elem& SLinkedList::front() const		// get front element
    { return head->elem; }

void SLinkedList::addFront(const Elem& e) {	// add to front of list
    SNode* v = new SNode;			// create new node
    v->elem = e;					// store data
    v->next = head;					// head now follows v
    head = v;						// v is now the head
}

void SLinkedList::removeFront() {		// remove front item
    SNode* old = head;				// save current head
    head = old->next;					// skip over old head
    delete old;						// delete the old head
}

int SLinkedList::sumRec() {
    return _sumRec(head);
}

int SLinkedList::_sumRec(SNode* node) {
    if (node ==NULL) {
        return 0;
    }
    else {
        return node->elem + _sumRec(node->next);
    }
}

void SLinkedList::_printRec(SNode* header) {
    if (header == NULL) {
        return;
    }
    else {
        cout << header->elem << '\t';
        _printRec(header->next);  
    }
 
}

void SLinkedList::printRec() {
    return _printRec(header);
}

void SLinkedList::_printReverseRec(SNode* header) {
    if (header == NULL) {
        return;
    }
    else {
        _printReverseRec(header->next);
        cout <<header->elem <<'\t';
    }
}

void SLinkedList::_printReverseRec(header) {
    return _printReverseRec(header);
}

bool SLinkedList::containsRec(int n, SNode* header) {
    if(header->elem == n) {
        return true;
    }
    else if (header == NULL) {
        return false;
    }
    else {
        return containsRec(n, header->next);
    }
}

SNode* SLinkedList:: _addTailRec (SNode* node, const Elem& e) {
    if (node->next == NULL) {
        SNode* v = new SNode;
        v->elem = e;
        v->next = NULL;
        node->next = v;
        return v;
    }
    else {
        node->next = _addTailRec(node->next, e);
        return node;
    }
}

SNode* SLinkedList::_reverseRec(SNode* node) {
    if (node == NULL || node->next == NULL) {
        return node;
    }
    else {
        SNode* n = _reverseRec(node->next);
        node->next->next = node;
        node->next = NULL;
        return n;
    }
}

int main( ) {
    SLinkedList a;				// list of integers
    a.addFront(1);
    a.addFront(2);
    a.addFront(3);
    a.addFront(4);

    return 0;
}