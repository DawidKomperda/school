#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Zadanie 1
class Node {
private:
    int value;
    Node* left;
    Node* right;
    Node* parent;
public:
    Node(int v, Node* l, Node* r, Node* p) {
        this->value = v;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    int getValue() { return value; }
    Node* getLeft() { return left; }
    Node* getRight() { return right; }
    Node* getParent() { return parent; }
    void setValue(int v) { value = v; }
    void setLeft(Node* l) { left = l; }
    void setRight(Node* r) { right = r; }
    void setParent(Node* p) { parent = p; }
};

class BSTree {
private:
    Node* root;

    // Helper method for delete operation to replace one subtree with another
    void transplant(Node* u, Node* v) {
        if (u->getParent() == nullptr) {
            root = v;
        } else if (u == u->getParent()->getLeft()) {
            u->getParent()->setLeft(v);
        } else {
            u->getParent()->setRight(v);
        }
        if (v != nullptr) {
            v->setParent(u->getParent());
        }
    }

public:
    BSTree() {
        root = nullptr;
    } // tworzy puste drzewo 

    Node* getRoot() {
        return root;
    } // zwraca wskażnik do root - metoda pomocnicza w testowaniu

    bool empty(Node* p) {
        return p == nullptr;
    } // zwraca prawdę gdy (pod)drzewo o korzeniu p jest puste

    void inorder(Node* p) {
        if (p != nullptr) {
            inorder(p->getLeft());
            cout << p->getValue() << " ";
            inorder(p->getRight());
        }
    } // wyświetla w porządku inorder

    // BST   
    void insert(int x) {
        Node* z = new Node(x, nullptr, nullptr, nullptr);
        Node* y = nullptr;
        Node* temp = root;
        while (temp != nullptr) {
            y = temp;
            if (z->getValue() < temp->getValue()) {
                temp = temp->getLeft();
            } else {
                temp = temp->getRight();
            }
        }
        z->setParent(y);
        if (y == nullptr) {
            root = z;
        } else if (z->getValue() < y->getValue()) {
            y->setLeft(z);
        } else {
            y->setRight(z);
        }
    } // wstawia węzeł z wartością x

    Node* search(int x) {
        Node* curr = root;
        while (curr != nullptr && x != curr->getValue()) {
            if (x < curr->getValue()) {
                curr = curr->getLeft();
            } else {
                curr = curr->getRight();
            }
        }
        return curr;
    } // zwraca wskaźnik do węzła z wartością x (lub NULL jeśli nie istnieje)

    Node* minimum(Node* p) {
        if (p == nullptr) return nullptr;
        while (p->getLeft() != nullptr) {
            p = p->getLeft();
        }
        return p;
    } // zwraca wskaźnik do węzła z minimalną wartością w (pod)drzewie p

    Node* maximum(Node* p) {
        if (p == nullptr) return nullptr;
        while (p->getRight() != nullptr) {
            p = p->getRight();
        }
        return p;
    } // zwraca wskaźnik do węzła z maksymalną wartością w (pod)drzewie p

    Node* successor(Node* p) {
        if (p == nullptr) return nullptr;
        if (p->getRight() != nullptr) {
            return minimum(p->getRight());
        }
        Node* y = p->getParent();
        while (y != nullptr && p == y->getRight()) {
            p = y;
            y = y->getParent();
        }
        return y;
    } // zwraca wskaźnik do następnika p

    Node* predecessor(Node* p) {
        if (p == nullptr) return nullptr;
        if (p->getLeft() != nullptr) {
            return maximum(p->getLeft());
        }
        Node* y = p->getParent();
        while (y != nullptr && p == y->getLeft()) {
            p = y;
            y = y->getParent();
        }
        return y;
    } // zwraca wskaźnik do poprzednika p

    void del(Node* z) {
        if (z == nullptr) return;

        if (z->getLeft() == nullptr) {
            transplant(z, z->getRight());
        } else if (z->getRight() == nullptr) {
            transplant(z, z->getLeft());
        } else {
            Node* y = minimum(z->getRight());
            if (y->getParent() != z) {
                transplant(y, y->getRight());
                y->setRight(z->getRight());
                y->getRight()->setParent(y);
            }
            transplant(z, y);
            y->setLeft(z->getLeft());
            y->getLeft()->setParent(y);
        }
        delete z;
    } // usuwa węzeł wskazywany przez p

    // Zadanie 2
    int size(Node* p) {
        if (p == nullptr) return 0;
        return 1 + size(p->getLeft()) + size(p->getRight());
    } // zwraca rozmiar (pod)drzewa o korzeniu p

    int hight(Node* p) {
        if (p == nullptr) return -1;
        return 1 + max(hight(p->getLeft()), hight(p->getRight()));
    } // zwraca wysokość (pod)drzewa o korzeniu p

    void clear(Node* p) {
        if (p == nullptr) return;
        
        clear(p->getLeft());
        clear(p->getRight());

        // Detach from parent to keep tree consistent if clearing a subtree
        if (p->getParent()) {
            if (p->getParent()->getLeft() == p) p->getParent()->setLeft(nullptr);
            else if (p->getParent()->getRight() == p) p->getParent()->setRight(nullptr);
        }
        // If clearing root, update root pointer
        if (p == root) {
            root = nullptr;
        }

        delete p;
    } // usuwa wszystkie węzły z (pod)drzewa o korzeniu p
};

int main() {
    // Zadanie 1 - test
    cout << endl << "Zadanie 1 - test" << endl;
    BSTree* t = new BSTree();

    cout << "Inserting: 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9" << endl;
    t->insert(15);
    t->insert(6);
    t->insert(18);
    t->insert(3);
    t->insert(7);
    t->insert(17);
    t->insert(20);
    t->insert(2);
    t->insert(4);
    t->insert(13);
    t->insert(9);

    cout << "Inorder traversal: ";
    t->inorder(t->getRoot());
    cout << endl;

    cout << "Search 13: " << (t->search(13) ? "Found" : "Not Found") << endl;
    cout << "Search 99: " << (t->search(99) ? "Found" : "Not Found") << endl;

    Node* minNode = t->minimum(t->getRoot());
    cout << "Minimum: " << (minNode ? to_string(minNode->getValue()) : "None") << endl;

    Node* maxNode = t->maximum(t->getRoot());
    cout << "Maximum: " << (maxNode ? to_string(maxNode->getValue()) : "None") << endl;

    Node* node7 = t->search(7);
    if (node7) {
        Node* succ = t->successor(node7);
        cout << "Successor of 7: " << (succ ? to_string(succ->getValue()) : "None") << endl;
        Node* pred = t->predecessor(node7);
        cout << "Predecessor of 7: " << (pred ? to_string(pred->getValue()) : "None") << endl;
    }

    cout << "Deleting 13 (node with one child 9)..." << endl;
    t->del(t->search(13));
    cout << "Inorder after delete 13: ";
    t->inorder(t->getRoot());
    cout << endl;

    cout << "Deleting 18 (node with two children 17, 20)..." << endl;
    t->del(t->search(18));
    cout << "Inorder after delete 18: ";
    t->inorder(t->getRoot());
    cout << endl;

    // Zadanie 2 - test
    cout << endl << "Zadanie 2 - test" << endl;
    
    cout << "Size of tree: " << t->size(t->getRoot()) << endl;
    cout << "Height of tree: " << t->hight(t->getRoot()) << endl;

    cout << "Clearing tree..." << endl;
    t->clear(t->getRoot());
    
    cout << "Tree empty? " << (t->getRoot() == nullptr ? "Yes" : "No") << endl;
    cout << "Size after clear: " << t->size(t->getRoot()) << endl;

    delete t;
    return 0;
}
