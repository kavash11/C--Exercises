//Kavya Sundaresan
//400307169
#include <list>
#include <iostream> 
using namespace std;

typedef int Elem;					                        // base element type
struct Node {					                            // a node of the tree
    Elem    elt;					                        // element value
    Node*   par;					                        // parent
    Node*   left;					                        // left child
    Node*   right;					                        // right child
    Node() : elt(), par(NULL), left(NULL), right(NULL), values(new Elem [1]), num(0), size(1) { }  // constructor
    Elem* values;
    Elem num;
    Elem size;
};

class Position {	 				                        // position in the tree
    private:
        Node* v;						                    // pointer to the node

    public:
        Position(Node* _v = NULL) : v(_v) { }                 // constructor            	        
        Elem& operator*()					                // get element
            { return v->elt; }
        Position left() const				                // get left child
            { return Position(v->left); }
        Position right() const				                // get right child
            { return Position(v->right); }
        Position parent() const				                // get parent
            { return Position(v->par); }
        bool isRoot() const				                    // root of the tree?
            { return v->par == NULL; }
        bool isNull() const				                    // root of the tree?
            { return v == NULL; }
        bool isExternal() const				                // an external node?
            { return v->left == NULL && v->right == NULL; }
        bool operator==(const Position& p) const	        // are equal?
            { return v == p.v; }
        bool operator!=(const Position& p) const			// are not equal?
            { return v != p.v; }
        Elem& getElem()	const				                // get element
            { return v->elt; }
        void addVal(const int x);
    friend class BinaryTree;			                    // give tree access
};

typedef list<Position> PositionList;                        // list of positions

class BinaryTree {
    public:
        BinaryTree();					                    // constructor
        int size() const;					                // number of nodes
        bool empty() const;					                // is tree empty?
        Position root() const;				                // get the root
        PositionList positions() const;  			        // list of nodes
        void addRoot();					                    // add root to empty tree
        void expandExternal(const Position& p);		        // expand external node
        Position removeAboveExternal(const Position& p);	// remove p and parent
        // housekeeping functions omitted...
    protected: 						                        // local utilities
        void preorder(const Position& v, PositionList& pl) const;	// preorder utility
    private:
        Node* _root;					                    // pointer to the root
        int n;						                        // number of nodes
};

BinaryTree::BinaryTree()			                        // constructor
    : _root(NULL), n(0) { }

int BinaryTree::size() const			                    // number of nodes
    { return n; }

bool BinaryTree::empty() const			                    // is tree empty?
    { return size() == 0; }

Position BinaryTree::root() const                           // get the root
    { return Position(_root); }

void BinaryTree::addRoot()			                        // add root to empty tree
    { _root = new Node; n = 1; }

void BinaryTree::expandExternal(const Position& p) {        // expand external node
    Node* v = p.v;					                        // p's node
    v->left = new Node;					                    // add a new left child
    v->left->par = v;					                    // v is its parent
    v->right = new Node;				                    // and a new right child
    v->right->par = v;					                    // v is its parent
    n += 2;						                            // two more nodes
}

PositionList BinaryTree::positions() const {                // list of all nodes
    PositionList pl;
    preorder(root(), pl);					                // preorder traversal
    return PositionList(pl);				                // return resulting list
}

void BinaryTree::preorder(const Position& v, PositionList& pl) const {  // preorder traversal
    pl.push_back(Position(v));				                // add this node
    if (!v.left().isExternal())					            // traverse left subtree
        preorder(v.left(), pl);
    if (!v.right().isExternal())					        // traverse right subtree
        preorder(v.right(), pl);
}

Position BinaryTree::removeAboveExternal(const Position& p) {   // this is needed for removal
    Node* w = p.v;  Node* v = w->par;			                // get p's node and parent
    Node* sib = (w == v->left ?  v->right : v->left);
    if (v == _root) {					                        // child of root?
      _root = sib;					                            // ...make sibling root
      sib->par = NULL;
    }
    else {
      Node* gpar = v->par;				                        // w's grandparent
      if (v == gpar->left) gpar->left = sib; 		            // replace parent by sib
      else gpar->right = sib;
      sib->par = gpar;
    }
    delete w; delete v;					                        // delete removed nodes
    n -= 2;						                                // two fewer nodes
    return Position(sib);
}

class KeyNotFoundException {
    private:
        string errMsg;
    public:
        KeyNotFoundException(const string& msg) {
            errMsg = msg;
        }
        string getMessage() const {
            return errMsg;
        }
};


class SearchTree {					                            // a binary search tree
    public: 						                            // public types
        class Iterator {	                      		        // an iterator/position
            private:
                Position v;						                // which entry
            public:
                Iterator(const Position& vv) : v(vv) { }		// constructor
                Elem& operator*() { return *v; }			    // get entry
                bool operator==(const Iterator& p) const		// are iterators equal?
                    { return v == p.v; }
                bool operator!=(const Iterator& p) const		// are iterators not equal?
                    { return v != p.v; }
                Iterator& operator++();				            // inorder successor
            friend class SearchTree;				            // give search tree access
        };
    public:						                                // public functions
        SearchTree();					                        // constructor
        int size() const; 					                    // number of entries
        bool empty() const;					                    // is the tree empty?
        SearchTree::Iterator find(const Elem& k);				// find entry with key k
        SearchTree::Iterator insert(const Elem& k, const Elem& x);		// insert (k,x)
        void erase(const Elem& k); //throw(NonexistentElement);	// remove key k entry
        void erase( SearchTree::Iterator& p);			        // remove entry at p
        SearchTree::Iterator begin();					        // iterator to first entry
        SearchTree::Iterator end();					            // iterator to end entry
        PositionList getPositionList();                         // ge the positions of the binary tree
        SearchTree::Iterator min();
        SearchTree::Iterator max();
        //int rank(Elem key);
        //Elem floor(Elem key);

    protected:						                            // local utilities
        Position root() const;					                // get virtual root
        Position finder(const Elem& k, const Position& v);		// find utility
        Position inserter(const Elem& k, const Elem& x);		// insert utility
        Position eraser(Position& w);				            // erase utility
        int _rank(Node *node, Elem key);
        
    private: 						                            // member data
        BinaryTree T;					                        // the binary tree
        int n;						                            // number of entries
};
			
SearchTree::SearchTree() : T(), n(0)                            // constructor
    { T.addRoot(); T.expandExternal(T.root()); }	            // create the super root
  
Position SearchTree::root() const                               // get virtual root
    { return T.root().left(); }				                    // left child of super root

int SearchTree::size() const                                    // get the size
    { return n; }

bool SearchTree::empty() const			                        // is search tree empty?
    { return size() == 0; }

SearchTree::Iterator SearchTree::begin() {                      // iterator to first entry
    Position v = root();					                    // start at virtual root
    while (!v.isExternal()) v = v.left();		                // find leftmost node
    return Iterator(v.parent());
}
  		
SearchTree::Iterator SearchTree::end()                          // iterator to end entry
    { return Iterator(T.root()); }			                    // return the super root

PositionList SearchTree::getPositionList(){                     // ge the positions of the binary tree
    return T.positions();
}
				
SearchTree::Iterator& SearchTree::Iterator::operator++() {      // inorder successor
    Position w = v.right();
    if (!w.isExternal()) {				                        // have right subtree?
      do { v = w; w = w.left(); }			                    // move down left chain
      while (!w.isExternal());
    }
    else {
      w = v.parent();					                        // get parent
      while (v == w.right())				                    // move up right chain
        { v = w; w = w.parent(); }
      v = w;						                            // and first link to left
    }
    return *this;
}
	
Position SearchTree::finder(const Elem& k, const Position& v) { // find utility
    if (v.isExternal()) return v;			                    // key not found
    if (k < v.getElem()) {return finder(k, v.left());}	        // search left subtree
    else if (v.getElem() < k) {return finder(k, v.right());}	    // search right subtree
    else return v;					                            // found it here
}
			
SearchTree::Iterator SearchTree::find(const Elem& k) {          // find entry with key k
    Position v = finder(k, root());				                // search from virtual root
    if (!v.isExternal()) return Iterator(v);		            // found it
    else return end();					                        // didn't find it
}
					
Position SearchTree::inserter(const Elem& k, const Elem& x) {  // insert utility
    Position y = finder(k, root());			
    	                // search from virtual root
    while (!y.isExternal()) { //not entering loop
        
        if (y.getElem() == k) {
            
            y.addVal(x);
            
            return y;
        }
        y = finder(k, y.right());	
    }
    			                       
    T.expandExternal(y);	
    *y = k;
    //not adding to left and right
    y.addVal(x); 
    //cout<<"&"<<root().left().right().getElem()<<endl;//noor
    n++;
    //cout<<"&"<<y.left().getElem()<<endl;//noor
    
    return y;						                            // return insert position
}

void Position::addVal(const int x) {
    if (v->size == v->num) {
        Elem* temp = new Elem[v->size*2];
        for (int i=0; i<v->num; i++) {
            temp[i] = v->values[i];
            v->size = v->size*2;
        }
        v->values = temp;
    }
    v->values[v->num] = x;
    v->num++;
    //cout << v->values[v->num-1]<<endl; //noor
}

SearchTree::Iterator SearchTree::insert(const Elem& k, const Elem& x)   // insert (k,x)
    {
         Position v = inserter(k, x); return Iterator(v); }

Position SearchTree::eraser(Position& w) {                          // remove utility
    Position z;
    if (w.left().isExternal()) z = w.left();		                // remove from left case 1
    else if (w.right().isExternal()) z = w.right();	                // remove from right case 1
    else {						                                    // both internal? case 2
      z = w.right();					                            // go to right subtree
      do { z = z.left(); } while (!z.isExternal());	                // get leftmost node
      Position v = z.parent();
      //w->setKey(v->key()); w->setValue(v->value());	            // copy z's parent to w
      *w = v.getElem();	                                            // copy z's parent to v
    }
    n--;						                                    // one less entry
    return T.removeAboveExternal(z);			                    // remove z and its parent
}
					
void SearchTree::erase(const Elem& k){ //throw(NonexistentElement) { // remove key k entry
    Position w = finder(k, root());				                    // search from virtual root
    // if (v.isExternal())					                        // not found?
    //   throw NonexistentElement("Erase of nonexistent");
    eraser(w);						                                // remove it
}
	
void SearchTree::erase( Iterator& p)                                // erase entry at p
    { eraser(p.v); }

SearchTree::Iterator SearchTree::min() {
    return begin();
}

SearchTree::Iterator SearchTree::max() {
    Iterator j = begin();
    Iterator i = begin();
    Elem max = 0;
    while (i!=end()) {
        if (*i >= max) {
            max  = *i;
            j = i;
        }
        ++i;
    }
    return j;
}
/*int SearchTree::rank(Elem key) {

    finder(key, T.root());
    return _rank(T.root(),key);
}

int SearchTree::_rank(Node *node, Elem key) {
    if (node == NULL) {
        throw KeyNotFoundException("The key is not found in the tree");
        return 0;
    }

}

Elem SearchTree::floor(Elem key) {
    
}*/

int main()
{
    cout << " Hi " << endl;

    SearchTree t;
    t.insert(23, 8);
    t.insert(18, 8);
    t.insert(4, 8);
    t.insert(5, 8);
    t.insert(40, 8);
    t.insert(3,8);
    t.insert(15,8);

    //cout << t.size() << endl;

    t.erase(15);

    //cout << t.size() << endl;

    //cout << t.positions() << endl;

    //list<Position> res = t.positions();

    typedef SearchTree::Iterator It;
    typedef list<int>::iterator ITList;
    for(It myit = t.begin() ; myit != t.end() ; ++myit){
        cout << *myit<< endl;
    }

    cout << " -- -- -- -- " << endl;
 
    list<Position> a = t.getPositionList();
    cout << a.front().getElem() << " -- " <<  a.size() << endl;

    cout << " -- " << endl;
    cout << *t.min() << endl;
    cout << *t.max() << endl;

    //cout << *t.floor(2) << endl;
 
    return 0;
}