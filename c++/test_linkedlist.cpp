#include <iostream>

using namespace std;

// Zadanie 1
class Element {
private:
    int v;
    Element* next;
    Element* prev;

public:
    Element(int x, Element* next, Element* prev) {
        this->v = x;
        this->next = next;
        this->prev = prev;
    }

    int getValue() { return v; }
    void setValue(int v) { this->v = v; }
    Element* getNext() { return next; }
    Element* getPrev() { return prev; }
    void setNext(Element* p) { next = p; }
    void setPrev(Element* p) { prev = p; }
};


class LinkedList {
private:
    Element* head;                    // pozycja pierwszego elementu
    Element* tail;                    // pozycja ostatniego elementu
    int size;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    bool empty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    void append(int x) {
        // wstawia element z x na końcu listy
        Element* newElem = new Element(x, nullptr, tail);
        if (empty()) {
            head = newElem;
            tail = newElem;
        } else {
            tail->setNext(newElem);
            tail = newElem;
        }
        size++;
    }

    void preppend(int x) {
        // wstawia element z x na początku listy
        Element* newElem = new Element(x, head, nullptr);
        if (empty()) {
            head = newElem;
            tail = newElem;
        } else {
            head->setPrev(newElem);
            head = newElem;
        }
        size++;
    }

    friend ostream& operator<<(ostream& out, LinkedList* l) {
        Element* curr = l->head;
        out << "[";
        while (curr != nullptr) {
            out << curr->getValue();
            if (curr->getNext() != nullptr) {
                out << ", ";
            }
            curr = curr->getNext();
        }
        out << "]";
        return out;
    }

    Element* locate(int x) {
        // zwraca pozycję pierwszego wystąpienia elementu z x, NULL jeśli x nie występuje
        Element* curr = head;
        while (curr != nullptr) {
            if (curr->getValue() == x) {
                return curr;
            }
            curr = curr->getNext();
        }
        return nullptr;
    }

    void clear() {
        // usuwa całą listę (zawartość)
        Element* curr = head;
        while (curr != nullptr) {
            Element* next = curr->getNext();
            delete curr;
            curr = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~LinkedList() {
        clear();
    }
};

int main() {
    // Zadanie 1 - Testowanie poprawności działania
    LinkedList* list = new LinkedList();

    cout << "--- TESTY LISTY DWUKIERUNKOWEJ ---" << endl;

    // 1. Test pustej listy
    cout << "\n1. Stan poczatkowy (pusta lista):" << endl;
    cout << "   empty() (oczekiwane 1): " << list->empty() << endl;
    cout << "   getSize() (oczekiwane 0): " << list->getSize() << endl;
    cout << "   Wypisanie: " << list << endl;

    // 2. Test append (dodawanie na koniec)
    cout << "\n2. Test append(10), append(20), append(30):" << endl;
    list->append(10);
    list->append(20);
    list->append(30);
    cout << "   empty() (oczekiwane 0): " << list->empty() << endl;
    cout << "   getSize() (oczekiwane 3): " << list->getSize() << endl;
    cout << "   Wypisanie (oczekiwane [10, 20, 30]): " << list << endl;

    // 3. Test preppend (dodawanie na początek)
    cout << "\n3. Test preppend(5), preppend(1):" << endl;
    list->preppend(5);
    list->preppend(1);
    cout << "   getSize() (oczekiwane 5): " << list->getSize() << endl;
    cout << "   Wypisanie (oczekiwane [1, 5, 10, 20, 30]): " << list << endl;

    // 4. Test locate (wyszukiwanie)
    cout << "\n4. Test locate:" << endl;
    int szukane[] = {10, 99};
    for (int x : szukane) {
        Element* el = list->locate(x);
        if (el != nullptr) {
            cout << "   locate(" << x << "): Znaleziono element o wartosci " << el->getValue() << endl;
            // Weryfikacja sąsiadów dla pewności spójności wskaźników
            if(el->getPrev()) cout << "      Poprzednik: " << el->getPrev()->getValue() << endl;
            if(el->getNext()) cout << "      Nastepnik: " << el->getNext()->getValue() << endl;
        } else {
            cout << "   locate(" << x << "): Nie znaleziono (NULL)" << endl;
        }
    }

    // 5. Test clear (czyszczenie)
    cout << "\n5. Test clear:" << endl;
    list->clear();
    cout << "   empty() (oczekiwane 1): " << list->empty() << endl;
    cout << "   getSize() (oczekiwane 0): " << list->getSize() << endl;
    cout << "   Wypisanie: " << list << endl;

    // 6. Test ponownego użycia po clear
    cout << "\n6. Dodawanie po clear (append 100):" << endl;
    list->append(100);
    cout << "   getSize() (oczekiwane 1): " << list->getSize() << endl;
    cout << "   Wypisanie: " << list << endl;

    delete list;
    return 0;
}
