#include <iostream>

using namespace std;

// --- Zadanie 1: Stos tablicowy ---

class ArrayStack {
private:
    int* items;
    int capacity;        // pojemność stosu
    int top;             // wierzchołek stosu (indeks)

public:
    ArrayStack(int c) {
        capacity = c;
        items = new int[capacity];
        top = -1; // Pusty stos
    }

    bool empty() {
        return top == -1;
    }

    bool full() {
        return top == capacity - 1;
    }

    void push(int x) {
        if (full()) {
            cout << "Blad: Stos pelny (Overflow)!" << endl;
            return;
        }
        items[++top] = x;
    }

    int peek() {
        if (empty()) {
            cout << "Blad: Stos pusty!" << endl;
            return 0; // Wartość domyślna w przypadku błędu
        }
        return items[top];
    }

    void pop() {
        if (empty()) {
            cout << "Blad: Stos pusty (Underflow)!" << endl;
            return;
        }
        top--;
    }

    void clear() {
        top = -1;
    }

    friend std::ostream& operator<<(std::ostream& out, ArrayStack& s) {
        out << "[";
        for (int i = 0; i <= s.top; i++) {
            out << s.items[i];
            if (i < s.top) out << ", ";
        }
        out << "] (top=" << s.top << ")";
        return out;
    }

    ~ArrayStack() {
        delete[] items;
    }
};

// --- Zadanie 2: Stos listowy ---

class Element {
private:
    int v;
    Element* next;
public:
    Element(int x, Element* next) {
        this->v = x;
        this->next = next;
    }
    int getValue() { return v; }
    Element* getNext() { return next; }
    void setNext(Element* p) { next = p; }
};

class LinkedStack {
private:
    Element* top;
public:
    LinkedStack() {
        top = nullptr;
    }

    bool empty() {
        return top == nullptr;
    }

    void push(int x) {
        // Nowy element staje się nowym wierzchołkiem i wskazuje na stary wierzchołek
        top = new Element(x, top);
    }

    int peek() {
        if (empty()) {
            cout << "Blad: Stos pusty!" << endl;
            return 0;
        }
        return top->getValue();
    }

    void pop() {
        if (empty()) {
            cout << "Blad: Stos pusty (Underflow)!" << endl;
            return;
        }
        Element* temp = top;
        top = top->getNext();
        delete temp;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    friend std::ostream& operator<<(std::ostream& out, LinkedStack* s) {
        out << "[Top -> ";
        Element* curr = s->top;
        while (curr != nullptr) {
            out << curr->getValue();
            if (curr->getNext() != nullptr) out << ", ";
            curr = curr->getNext();
        }
        out << "]";
        return out;
    }

    ~LinkedStack() {
        clear();
    }
};

int main() {
    // --- TESTY ZADANIE 1 (ArrayStack) ---
    cout << "=== ZADANIE 1: ArrayStack (Pojemnosc: 3) ===" << endl;
    ArrayStack s1(3);

    cout << "1. Stan poczatkowy:" << endl;
    cout << "   empty() (oczekiwane 1): " << s1.empty() << endl;
    cout << "   full()  (oczekiwane 0): " << s1.full() << endl;
    cout << "   Zawartosc: " << s1 << endl;

    cout << "\n2. Wypelnianie stosu (push 10, 20, 30):" << endl;
    s1.push(10);
    s1.push(20);
    s1.push(30);
    cout << "   Zawartosc: " << s1 << endl;
    cout << "   full() (oczekiwane 1): " << s1.full() << endl;
    cout << "   peek() (oczekiwane 30): " << s1.peek() << endl;

    cout << "\n3. Przepełnienie (push 40 na pelny stos):" << endl;
    cout << "   Komunikat: "; s1.push(40);
    cout << "   Zawartosc: " << s1 << endl;

    cout << "\n4. Zdejmowanie elementow (pop, pop):" << endl;
    s1.pop(); // usuwa 30
    cout << "   Po 1 pop (oczekiwane 20 na topie): " << s1 << ", peek: " << s1.peek() << endl;
    s1.pop(); // usuwa 20
    cout << "   Po 2 pop (oczekiwane 10 na topie): " << s1 << ", peek: " << s1.peek() << endl;

    cout << "\n5. Wyczyszczenie (clear):" << endl;
    s1.clear();
    cout << "   empty() (oczekiwane 1): " << s1.empty() << endl;
    cout << "   Zawartosc: " << s1 << endl;

    cout << "\n6. Pop na pustym stosie:" << endl;
    cout << "   Komunikat: "; s1.pop();


    // --- TESTY ZADANIE 2 (LinkedStack) ---
    cout << "\n\n=== ZADANIE 2: LinkedStack ===" << endl;
    LinkedStack* s2 = new LinkedStack();

    cout << "1. Stan poczatkowy:" << endl;
    cout << "   empty() (oczekiwane 1): " << s2->empty() << endl;
    cout << "   Zawartosc: " << s2 << endl;

    cout << "\n2. Dodawanie elementow (push 5, 15, 25):" << endl;
    s2->push(5);
    s2->push(15);
    s2->push(25);
    cout << "   Zawartosc: " << s2 << endl;
    cout << "   peek() (oczekiwane 25): " << s2->peek() << endl;

    cout << "\n3. Zdejmowanie elementow (pop):" << endl;
    s2->pop(); // usuwa 25
    cout << "   Po pop (oczekiwane 15 na topie): " << s2 << ", peek: " << s2->peek() << endl;

    cout << "\n4. Wyczyszczenie (clear):" << endl;
    s2->clear();
    cout << "   empty() (oczekiwane 1): " << s2->empty() << endl;
    cout << "   Zawartosc: " << s2 << endl;

    cout << "\n5. Pop na pustym stosie:" << endl;
    cout << "   Komunikat: "; s2->pop();

    delete s2;
    return 0;
}
