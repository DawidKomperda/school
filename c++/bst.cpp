#include <iostream>

using namespace std;

class Node{
    private:
        int value;
        Node* left;
        Node* right;
        Node* parent;
    public:
        Node(int v, Node* l, Node* r, Node* p);
        int getValue();
        Node* getLeft();
        Node* getRight();
        Node* getParent();
        void setValue(int v);
        void setLeft(Node* l);
        void setRight(Node* r);
        void setParent(Node* p);
};

class BSTree{
    private:
        Node* root;
    public:
        BSTree();                        //tworzy puste drzewo 
  
        Node* getRoot();            //zwraca wskażnik do root - metoda pomocnicza w testowaniu
        bool empty(Node* p);        //zwraca prawdę gdy (pod)drzewo o korzeniu p jest puste
        void inorder(Node* p);      //wyświetla w porządku inorder
    //BST   
        void insert(int x);            //wstawia węzeł z wartością x
        Node* search(int x);         //zwraca wskaźnik do węzła z wartością x (lub NULL jeśli nie istnieje)
        Node* minimum(Node* p);            //zwraca wskaźnik do węzła z minimalną wartością w (pod)drzewie p
        Node* maximum(Node* p);            //zwraca wskaźnik do węzła z maksymalną wartością w (pod)drzewie p
        Node* successor(Node* p);    //zwraca wskaźnik do następnika p
        Node* predecessor(Node* p);    //zwraca wskaźnik do poprzednika p
        void del(Node* p);            //usuwa węzeł wskazywany przez p
};


Node::Node(int v, Node* l, Node* r, Node* p){
    this->value = v;
    this->left = l;
    this->right = r;
    this->parent = p;

}
Node* Node::getLeft(){
    return left;
}
Node* Node::getRight(){
    return right;
}
Node* Node::getParent(){
    return parent;
}

void Node::setValue(int v){
    this->value = v;
}

void Node::setLeft(Node* l){
    this->left = l;
}

void Node::setRight(Node* r){
    this->right = r;
}

void Node::setParent(Node* p){
    this->parent = p;
}
BSTree::BSTree(){
    root = nullptr;
}

Node* BSTree::getRoot(){
    return root;
}

bool BSTree::empty(Node* p){
    if(p->getLeft() == nullptr && p->getRight() == nullptr){
        return true;
    }
    else{ return false;}
}

int Node::getValue(){
    return value;
}

void BSTree::inorder(Node* p){
    if(root == nullptr){
        cout<<"It's empty";
        return;
    }
    inorder(p->getLeft());

    cout << p->getValue() << " ";

    inorder(p->getRight());
    
}

Node* BSTree::search(int x){
    if(root = nullptr){
        cout <<"It's empty";
        return;
    }

    Node* curr = root;
    while(curr != nullptr){
        if(curr->getValue() == x){
            cout<<"found it";
            return curr;
        }
        if(curr->getValue() > x){
            curr = curr->getLeft();
            cout<<"found it";
            return curr;
        }
        else{
            curr = curr->getRight();
            cout<<"found it";
            return curr;
        }
    }
    cout<<"didn't found it";
    return;
}

void BSTree::insert(int x){
    Node* newNode = new Node(x, nullptr, nullptr, nullptr);
    if(root == nullptr){
        root = newNode;
        return;
    }

    Node* curr = root;
    Node* parent = nullptr;

    while(curr != nullptr){
        parent = curr;
        if(x < curr->getValue()){
            curr = curr->getLeft();
        } else {
            curr = curr->getRight();
        }
    }

    newNode->setParent(parent);
    if(x < parent->getValue()){
        parent->setLeft(newNode);
    } else {
        parent->setRight(newNode);
    }
}
main(){
cout<<endl<<"Zadanie 1 - test"<<endl;
BSTree* t = new BSTree();

}
