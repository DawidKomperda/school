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

    void insert(Element* p, int x) {
        // wstawia element z wartością x na pozycję (wskazywaną przez) p (przed p)
        if (p == nullptr) return;
        if (p == head) {
            preppend(x);
            return;
        }
        Element* newElem = new Element(x, p, p->getPrev());
        if (p->getPrev()) {
            p->getPrev()->setNext(newElem);
        }
        p->setPrev(newElem);
        size++;
    }

    void del(Element* p) {
        // usuwa element z pozycji (wskazywanej przez) p
        if (p == nullptr) return;
        
        if (p == head) {
            head = p->getNext();
            if (head) head->setPrev(nullptr);
            else tail = nullptr;
        } else if (p == tail) {
            tail = p->getPrev();
            if (tail) tail->setNext(nullptr);
            else head = nullptr;
        } else {
            if (p->getPrev()) p->getPrev()->setNext(p->getNext());
            if (p->getNext()) p->getNext()->setPrev(p->getPrev());
        }
        delete p;
        size--;
    }

    void deleteX(int x) {
        // usuwa pierwsze wystąpienie elementu o wartości x
        Element* p = locate(x);
        if (p != nullptr) {
            del(p);
        }
    }

    Element* getFirst() { return head; }
    Element* getLast() { return tail; }
    Element* getNext(Element *p) { return (p) ? p->getNext() : nullptr; }
    Element* getPrev(Element *p) { return (p) ? p->getPrev() : nullptr; }
    int retrive(Element* p) { return (p) ? p->getValue() : 0; }

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

// Zadanie 2
class SortedLinkedList {
private:
    Element* head;                    // pozycja pierwszego elementu
    Element* tail;                    // pozycja ostatniego elementu
    int size;

public:
    SortedLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~SortedLinkedList() {
        clear();
    }

    void clear() {
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

    bool empty() {
        return size == 0;
    }

    void insertSorted(int x) {
        Element* newElem = new Element(x, nullptr, nullptr);

        // Przypadek 1: Lista pusta
        if (empty()) {
            head = newElem;
            tail = newElem;
        } 
        // Przypadek 2: Wstawianie na początek (x mniejszy lub równy head)
        else if (x <= head->getValue()) {
            newElem->setNext(head);
            head->setPrev(newElem);
            head = newElem;
        } 
        // Przypadek 3: Wstawianie na koniec (x większy lub równy tail)
        else if (x >= tail->getValue()) {
            newElem->setPrev(tail);
            tail->setNext(newElem);
            tail = newElem;
        } 
        // Przypadek 4: Wstawianie w środek
        else {
            Element* curr = head->getNext();
            while (curr != nullptr) {
                if (x <= curr->getValue()) {
                    Element* prev = curr->getPrev();
                    
                    // Wpinanie newElem między prev a curr
                    prev->setNext(newElem);
                    newElem->setPrev(prev);
                    
                    newElem->setNext(curr);
                    curr->setPrev(newElem);
                    break;
                }
                curr = curr->getNext();
            }
        }
        size++;
    }

    friend ostream& operator<<(ostream& out, SortedLinkedList* l) {
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

    // 7. Test insert (wstawianie przed element)
    cout << "\n7. Test insert(15) przed 20:" << endl;
    // Przywracamy stan listy do testu
    list->clear();
    list->append(10);
    list->append(20);
    list->append(30);
    Element* el20 = list->locate(20);
    list->insert(el20, 15);
    cout << "   Wypisanie (oczekiwane [10, 15, 20, 30]): " << list << endl;

    // 8. Test deleteX
    cout << "\n8. Test deleteX(15):" << endl;
    list->deleteX(15);
    cout << "   Wypisanie (oczekiwane [10, 20, 30]): " << list << endl;

    // 9. Test del (usuwanie wskaznika)
    cout << "\n9. Test del(head):" << endl;
    list->del(list->getFirst());
    cout << "   Wypisanie (oczekiwane [20, 30]): " << list << endl;

    // 10. Testy akcesorow
    cout << "\n10. Testy akcesorow:" << endl;
    if (!list->empty()) {
        cout << "   First: " << list->retrive(list->getFirst()) << endl;
        cout << "   Last: " << list->retrive(list->getLast()) << endl;
    }

    delete list;

    // Zadanie 2 - Testowanie SortedLinkedList
    cout << "\n--- TESTY SORTED LINKED LIST (Zadanie 2) ---" << endl;
    SortedLinkedList* sList = new SortedLinkedList();

    // 1. Wstawianie do pustej listy
    cout << "1. Wstawianie 10 (do pustej listy):" << endl;
    sList->insertSorted(10);
    cout << "   Lista: " << sList << endl;

    // 2. Wstawianie elementu mniejszego (na początek)
    cout << "2. Wstawianie 5 (na poczatek):" << endl;
    sList->insertSorted(5);
    cout << "   Lista: " << sList << endl;

    // 3. Wstawianie elementu większego (na koniec)
    cout << "3. Wstawianie 20 (na koniec):" << endl;
    sList->insertSorted(20);
    cout << "   Lista: " << sList << endl;

    // 4. Wstawianie elementu w środek
    cout << "4. Wstawianie 15 (w srodek):" << endl;
    sList->insertSorted(15);
    cout << "   Lista: " << sList << endl;

    // 5. Wstawianie duplikatu
    cout << "5. Wstawianie 15 (duplikat):" << endl;
    sList->insertSorted(15);
    cout << "   Lista: " << sList << endl;

    // 6. Wstawianie kolejnych elementów w losowej kolejności
    cout << "6. Wstawianie 8, 25, 1:" << endl;
    sList->insertSorted(8);
    sList->insertSorted(25);
    sList->insertSorted(1);
    cout << "   Lista: " << sList << endl;

    delete sList;

    return 0;
}
