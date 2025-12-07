#include <iostream>

using namespace std;

// Klasa Element (pomocnicza dla Zadania 4)
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

// --- Zadanie 3: Kolejka tablicowa (Cykliczna) ---
class ArrayFifo {
private:
    int* items;
    int capacity;            // pojemność kolejki
    int size;                // rozmiar kolejki (liczba elementów)
    int head;                // indeks pierwszego elementu
    int tail;                // indeks ostatniego elementu

public:
    ArrayFifo(int c) {
        capacity = c;
        items = new int[capacity];
        size = 0;
        head = 0;
        tail = -1;
    }

    bool empty() {
        return size == 0;
    }

    bool full() {
        return size == capacity;
    }

    void enqueue(int x) {
        if (full()) {
            cout << "Blad: Kolejka pelna!" << endl;
            return;
        }
        // Obliczamy nowy indeks ogona (cyklicznie)
        tail = (tail + 1) % capacity;
        items[tail] = x;
        size++;
    }

    int peek() {
        if (empty()) {
            cout << "Blad: Kolejka pusta!" << endl;
            return 0;
        }
        return items[head];
    }

    void dequeue() {
        if (empty()) {
            cout << "Blad: Kolejka pusta!" << endl;
            return;
        }
        // Przesuwamy glowe (cyklicznie)
        head = (head + 1) % capacity;
        size--;
        
        // Reset indeksów dla czystości (opcjonalne w buforze cyklicznym, ale pomocne w debugowaniu)
        if (size == 0) {
            head = 0;
            tail = -1;
        }
    }

    void clear() {
        size = 0;
        head = 0;
        tail = -1;
    }

    friend std::ostream& operator<<(std::ostream& out, ArrayFifo& f) {
        out << "[";
        if (!f.empty()) {
            int count = 0;
            int i = f.head;
            while (count < f.size) {
                out << f.items[i];
                if (count < f.size - 1) {
                    out << ", ";
                }
                i = (i + 1) % f.capacity;
                count++;
            }
        }
        out << "] (size=" << f.size << ", head=" << f.head << ", tail=" << f.tail << ")";
        return out;
    }

    ~ArrayFifo() {
        delete[] items;
    }
};

// --- Zadanie 4: Kolejka listowa ---
class LinkedFifo {
private:
    Element* head;
    Element* tail;
public:
    LinkedFifo() {
        head = nullptr;
        tail = nullptr;
    }

    bool empty() {
        return head == nullptr;
    }

    void enqueue(int x) {
        Element* newElem = new Element(x, nullptr);
        if (empty()) {
            head = newElem;
            tail = newElem;
        } else {
            tail->setNext(newElem);
            tail = newElem;
        }
    }

    int peek() {
        if (empty()) {
            cout << "Blad: Kolejka pusta!" << endl;
            return 0;
        }
        return head->getValue();
    }

    void dequeue() {
        if (empty()) {
            cout << "Blad: Kolejka pusta!" << endl;
            return;
        }
        Element* temp = head;
        head = head->getNext();
        
        if (head == nullptr) {
            tail = nullptr; // Kolejka stała się pusta
        }
        
        delete temp;
    }

    void clear() {
        while (!empty()) {
            dequeue();
        }
    }

    friend std::ostream& operator<<(std::ostream& out, LinkedFifo* f) {
        out << "[Head -> ";
        Element* curr = f->head;
        while (curr != nullptr) {
            out << curr->getValue();
            if (curr->getNext() != nullptr) out << ", ";
            curr = curr->getNext();
        }
        out << " <- Tail]";
        return out;
    }

    ~LinkedFifo() {
        clear();
    }
};

int main() {
    // --- TESTY ZADANIE 3 (ArrayFifo) ---
    cout << "=== ZADANIE 3: ArrayFifo (Pojemnosc: 3) ===" << endl;
    ArrayFifo q1(3);

    cout << "1. Stan poczatkowy:" << endl;
    cout << "   empty() (oczekiwane 1): " << q1.empty() << endl;
    cout << "   full()  (oczekiwane 0): " << q1.full() << endl;
    cout << "   Zawartosc: " << q1 << endl;

    cout << "\n2. Wypelnianie kolejki (enqueue 10, 20, 30):" << endl;
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    cout << "   Zawartosc: " << q1 << endl;
    cout << "   full() (oczekiwane 1): " << q1.full() << endl;
    cout << "   peek() (oczekiwane 10): " << q1.peek() << endl;

    cout << "\n3. Przepełnienie (enqueue 40 na pelna kolejke):" << endl;
    cout << "   Komunikat: "; q1.enqueue(40);

    cout << "\n4. Obsluga bufora cyklicznego:" << endl;
    q1.dequeue(); // Usuwamy 10
    cout << "   Po dequeue (usunieto 10): " << q1 << endl;
    cout << "   peek() (oczekiwane 20): " << q1.peek() << endl;
    
    q1.enqueue(40); // Dodajemy 40 (powinno wejsc na indeks 0)
    cout << "   Po enqueue(40) (cykliczne wstawienie): " << q1 << endl;

    cout << "\n5. Oproznianie kolejki:" << endl;
    q1.dequeue(); // usuwa 20
    q1.dequeue(); // usuwa 30
    q1.dequeue(); // usuwa 40
    cout << "   Po 3x dequeue: " << q1 << endl;
    cout << "   empty() (oczekiwane 1): " << q1.empty() << endl;

    cout << "\n6. Dequeue na pustej kolejce:" << endl;
    cout << "   Komunikat: "; q1.dequeue();


    // --- TESTY ZADANIE 4 (LinkedFifo) ---
    cout << "\n\n=== ZADANIE 4: LinkedFifo ===" << endl;
    LinkedFifo* q2 = new LinkedFifo();

    cout << "1. Stan poczatkowy:" << endl;
    cout << "   empty() (oczekiwane 1): " << q2->empty() << endl;
    cout << "   Zawartosc: " << q2 << endl;

    cout << "\n2. Dodawanie elementow (enqueue 5, 15, 25):" << endl;
    q2->enqueue(5);
    q2->enqueue(15);
    q2->enqueue(25);
    cout << "   Zawartosc: " << q2 << endl;
    cout << "   peek() (oczekiwane 5): " << q2->peek() << endl;

    cout << "\n3. Usuwanie elementow (dequeue):" << endl;
    q2->dequeue(); // usuwa 5
    cout << "   Po dequeue (oczekiwane 15 na poczatku): " << q2 << endl;
    cout << "   peek() (oczekiwane 15): " << q2->peek() << endl;

    cout << "\n4. Wyczyszczenie (clear):" << endl;
    q2->clear();
    cout << "   empty() (oczekiwane 1): " << q2->empty() << endl;
    cout << "   Zawartosc: " << q2 << endl;

    cout << "\n5. Dequeue na pustej kolejce:" << endl;
    cout << "   Komunikat: "; q2->dequeue();

    delete q2;
    return 0;
}
