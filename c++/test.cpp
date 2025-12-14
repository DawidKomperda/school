#include <iostream>
using namespace std;

class Node
{

private:
    int value;

    Node *left;

    Node *right;

public:
    Node(int v, Node *l = nullptr, Node *r = nullptr)
    {
        value = v;
        left = l;
        right = r;
    };

    int getValue() { return value; };

    Node *getLeft() { return left; };

    Node *getRight() { return right; };

    void setValue(int v) { value = v; };

    void setLeft(Node *l) { left = l; };

    void setRight(Node *p) { right = p; };
};

class BST
{

private:
    Node *root;

public:
    BST(Node *r) { root = r; } // konstruktor tworzący drzewo o korzeniu r

    Node *search(int x)
    {
        Node *temp = root;
        while (temp != nullptr)
        {
            if (temp->getValue() == x)
            {
                return temp;
            }
            if (x < temp->getValue())
            {
                temp = temp->getLeft();
            }
            else
            {
                temp = temp->getRight();
            }
        }
        return nullptr;
    }; // x - wartość szukana, wersja iteracyjna

    int size(Node *n)
    {
        if (n == nullptr)
        {
            return 0;
        }
        return 1 + size(n->getLeft()) + size(n->getRight());
    }; // zwraca liczbę węzłów w drzewie

    int size() { return size(root); } // metoda pomocnicza do testów
};

int main()
{
    // Build small tree:
    //        10
    //       /  \
    //      5   15
    //     / \    \
    //    3   7    20
    Node *n10 = new Node(10);
    Node *n5 = new Node(5);
    Node *n15 = new Node(15);
    Node *n3 = new Node(3);
    Node *n7 = new Node(7);
    Node *n20 = new Node(20);

    n10->setLeft(n5);
    n10->setRight(n15);
    n5->setLeft(n3);
    n5->setRight(n7);
    n15->setRight(n20);

    BST tree(n10);

    cout << "Size (expected 6): " << tree.size() << endl;

    int tests[] = {10, 3, 20, 8}; // last one (8) not present
    for (int x : tests)
    {
        Node *res = tree.search(x);
        cout << "Search " << x << ": " << (res ? "Found" : "Not Found");
        if (res)
            cout << " (value=" << res->getValue() << ")";
        cout << endl;
    }

    // cleanup nodes (no destructor provided)
    delete n3;
    delete n7;
    delete n5;
    delete n20;
    delete n15;
    delete n10;
    return 0;
}