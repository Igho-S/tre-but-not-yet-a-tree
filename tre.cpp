#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

class Node{//class for node
    int key;
    Node* left, *right;
    
    public:
    
    Node(int k = 0, Node*l = NULL, Node*r = NULL){
        key = k, 
        left = l, 
        right = r;
    }
    friend class Tree;
};

class Tree{//class for tree
    Node* root;
    
    public:
    
    Tree(){root = NULL;}//make the root 0
    Tree(int n);//which fills random numbers to tree with n edges
    Tree(const Tree&);
    Node * Tree_cpy(Node* n);
    ~Tree();
    
    void Add(int k);
    Node* GetRoot(){return root;}
    void Deletet(Node* q);
    Tree& operator = (Tree&);
    void printt(Node*, int);
    Node* search(int);
    int min();
    int max();
};

Tree::Tree(int n){//makes n random numbers
/*it is done basically on the adding function in tree. we 
create node q and fill with rand numbers
make q the root and reduce n\and make, while n > 0, we add random numbers and reduce n*/
    Node*q = new Node(rand() % 100);
    root = q; 
    n--;
    while (n > 0){
        Add(rand() % 100);
        n--;
    }
}

Tree::Tree(const Tree&D){
    /*copy constructor. here, make the root of empty tree = 0 so, the root which we create is also = 0.
    else, ie if not empty, we create a root with key and to the left and right of tree, 
    we take the function of copy.*/
    if(D.root == NULL) root == NULL;
    else{
        root = new Node(D.root -> key);
        root -> left = Tree_cpy(D.root->left);
        root -> right = Tree_cpy(D.root -> right);
    }
}

Node* Tree::Tree_cpy(Node* n){
    /*if empty the return 0. we make a node and for left and right, we copy left and right elements and we return p*/
    if(n == NULL) return NULL;
    Node* p = new Node(n -> key);
    p -> left = Tree_cpy(n -> left);
    p -> right = Tree_cpy(n -> right);
    return p;
}

void Tree::Add(int k){
    /*to add Node
    we make an empty node and while it is not empty, we make the new node as our root
    and if the key is less than right key, we add to left and if otherwise, we add to right.*/ 
    Node* j = new Node;
    Node *r = root;
    while (r != NULL){
        j = r;
        if(k < r -> key) r = r -> left;
        else r = r -> right;
    }
    Node *p = new Node(k);//here, we check if k is < j if that then we add the new node to
    //left and else, we add to right.
    if(k < j -> key) j -> left = p;
    else j -> right = p;
}

Node * Tree::search(int s){
    /*node r root, if the root and s are not equal to the key r we
    also we go down to the left if < and else, go to the right..
    and if the kjey is not in the key, it returns 0
    if not found, then r becomes 0 (dopustovo dereva i r = 0).*/
    
    Node* r = root;
    while(r&&s != r -> key){
        if(s < r-> key) r = r -> left;
        else r = r -> right;
    }
    return r;
}

int Tree::min(){
    /*here, we go down and if the leftmost node is not equal to 0, we 
    output the node to the key and output the key */
    Node * r = root;
    while(r -> left != NULL) r = r -> left;
    return r -> key;
}

int Tree::max(){
    /*for max, similarly, we go down and if the rightmost node is not empty, we 
    output the node to key and we return r.*/
    Node* r = root;
    while( r-> right != NULL) r = r -> right;
    return r -> key;
}

Tree::~Tree(){
    /*destructor, it is used recursively. we deine some function for the root*/
    Deletet(root);
}

void Tree::Deletet(Node* q){
    if(q){
        /*and here, if the root exists, we change the left subtree, right subtree and then delete the node itself.*/
        Deletet(q -> left);
        Deletet(q -> right);
        delete q;
    }
}

Tree& Tree::operator = (Tree&D){
    /*similar to copy constructor. it takes function we delete on root
    and make new node by key and further takes the function for left and right subtree*/
    if (D.root == NULL) root = NULL;
    else{
        Deletet(root);
        root = new Node(D.root -> key);
        root -> left = Tree_cpy(D.root -> left);
        root -> right = Tree_cpy(D.root -> right);
    }
    return *this;
}

void Tree::printt(Node *q, int k){

    if(q == NULL) return;
    printt(q -> left, k+ 5);
    
    for(int i = 0; i < k; i++) cout << " ";
    cout << q -> key << endl;
    printt(q -> right, k + 5);
}

int main(void){
    srand(time(0));
    Tree d(7);
    d.printt(d.GetRoot(), 0);
    cout << endl;
    Tree e(d);
    e.printt(e.GetRoot(), 0);
    cout << endl;
    Tree i = e;
    i.printt(i.GetRoot(), 0);
    cout << endl;
    i.Add(50);
    i.printt(i.GetRoot(),0);
    cout << endl;
    if(i.search(54) != NULL) cout << "Found " <<endl;
    else cout << "Not Found!" << endl;
    int min, max;
    min = i.min();
    max = i.max();
    cout <<" min element: " << min << endl << "Max element: " << max << endl;

    return 0;
}

