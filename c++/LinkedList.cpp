#include <iostream>

using namespace std;

class Element
{
private:
    int v;
    Element *next;
    Element *prev;

public:
    Element(int x, Element *next, Element *prev)
    {
        this->v = x;
        this->next = next;
        this->prev = prev;
    }; // tworzy element przechowujący x
    int getValue() { return this->v; };           // zwraca wartość
    void setValue(int v) { this->v = v; };        // ustawia warość v
    Element *getNext() { return this->next; };    // zwraca ozycję następnego elementu
    Element *getPrev() { return this->prev; };    // zwraca pozycję poprzedniego elementu
    void setNext(Element *p) { this->next = p; }; // ustawia p jako następny element
    void setPrev(Element *p) { this->prev = p; }; // ustawia p jako poprzedni element
};

class LinkedList
{
private:
    Element *head; // pozycja pierwszego elementu
    Element *tail; // pozycja ostatniego elementu
    int size;

public:
    LinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }; // tworzy pustą listę
    bool empty() { return size == 0; }; // zwraca prawdę jeśli lista pusta, fałsz w przeciwnym przypadku
    int getSize() { return size; };     // zwraca wielkość listy (liczbę elementów w liście)
     Element* getFirst(){return head;};                         //zwraca pozycję (wskaźnik do) pierwszego elementu listy
     Element* getLast(){return tail;};                               //zwraca pozycję (wskaźnik do) ostatniego elementu listy
    Element* getNext(Element *p)
    {
        if (p == nullptr)
        {
            return nullptr;
        }
        return p->getNext();
    }; // zwraca pozycję (wskaźnik do) następnego elementu listy
    Element* getPrev(Element *p)
    {
        if (p == nullptr)
        {
            return nullptr;
        }
        return p->getPrev();
    }; // zwraca pozycję (wskaźnik do) poprzedniego elementu listy
     int retrive(Element* p){return p->getValue();};                   //zwraca element (wartość) z pozycji (wskazywanej przez) p
    void append(int x)
    {
        Element *dot = new Element(x, nullptr, nullptr);
        if (empty())
        {
            this->head = dot;
            this->tail = dot;
        }
        else
        {
            tail->setNext(dot);
            dot->setPrev(this->tail);
            this->tail = dot;
        }
        this->size++;
    }; // wstawia element z x na końcu listy
    void preppend(int x)
    {
        Element *dot = new Element(x, nullptr, nullptr);
        if (empty())
        {
            this->tail = dot;
            this->head = dot;
        }
        else
        {
            head->setPrev(dot);
            dot->setNext(this->head);
            head = dot;
        }
        this->size++;
    }; // wstawia element z x na początku listy
    friend ostream &operator<<(ostream &out, LinkedList *l)
    {
        out << "[";
        Element *curr = l->head;
        while (curr != nullptr)
        {
            out << curr->getValue(); // Use 'out' instead of 'cout'
            if (curr->getNext() != nullptr)
            {
                out << ", "; // Add a comma and space between elements
            }
            curr = curr->getNext();
        }
        out << "]";
        return out;
    }; // wypisuje elementu listy

    Element *locate(int x)
    {
        Element *curr = head;
        while (curr != nullptr)
        {
            if (curr->getValue() == x)
            {
                return curr;
            }
            else
            {
                curr = curr->getNext();
            }
        }
        return nullptr;
    }; // zwraca pozycję pierwszego wystąpienia elementu z x, NULL jeśli x nie występuje
    void clear()
    {
        Element *curr = head;
        while (curr != nullptr)
        {
            Element *next = curr->getNext();
            delete curr;
            curr = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }; // usuwa całą listę (zawartość)
    void insert(Element* p, int x){
        if(p == nullptr){return;}
        Element* dot = new Element(x, nullptr, nullptr);
        if(p == tail){
            p->setNext(dot);
            dot->setPrev(p);
            tail = dot;
        }
        else{
            dot->setNext(p->getNext());
            dot->setPrev(p);
            p->getNext()->setPrev(dot);
            p->setNext(dot);
        }

        this->size++;
    };              //wstawia element z wartością x na pozycję (wskazywaną przez) p   
    void del(Element* p){
        if(p == nullptr) return;

        // 1. Handle the "Previous" side
        if (p->getPrev() != nullptr) {
            p->getPrev()->setNext(p->getNext());
        } else {
            this->head = p->getNext(); // p was head
        }

        // 2. Handle the "Next" side
        if (p->getNext() != nullptr) {
            p->getNext()->setPrev(p->getPrev());
        } else {
            this->tail = p->getPrev(); // p was tail
        }

        delete p;
        this->size--;
    };                            //usuwa element z pozycji (wskazywanej przez) p       
    void deleteX(int x)
    {
        Element *p = locate(x);
        if (p != nullptr)
        {
            del(p);
        }
    };              //usuwa pierwsze wystąpienie elementu o wartości x
    ~LinkedList()
    {
        clear();
    };
};

int main()
{

    // Zadanie 1 - Testowanie poprawności działania
    LinkedList *list = new LinkedList();

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
    for (int x : szukane)
    {
        Element *el = list->locate(x);
        if (el != nullptr)
        {
            cout << "   locate(" << x << "): Znaleziono element o wartosci " << el->getValue() << endl;
            // Weryfikacja sąsiadów dla pewności spójności wskaźników
            if (el->getPrev())
                cout << "      Poprzednik: " << el->getPrev()->getValue() << endl;
            if (el->getNext())
                cout << "      Nastepnik: " << el->getNext()->getValue() << endl;
        }
        else
        {
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

    // 7. Test insert (wstawianie w środku)
    cout << "\n7. Test insert:" << endl;
    list->clear();
    list->append(10);
    list->append(30);
    Element* el = list->locate(10);
    if(el != nullptr) {
        list->insert(el, 20); // Insert 20 after 10
    }
    cout << "   Wypisanie (oczekiwane [10, 20, 30]): " << list << endl;

    // 8. Test del (usuwanie)
    cout << "\n8. Test del:" << endl;
    // Delete middle
    Element* toDel = list->locate(20);
    list->del(toDel);
    cout << "   Po usunieciu 20 (oczekiwane [10, 30]): " << list << endl;
    
    // Delete head
    toDel = list->locate(10);
    list->del(toDel);
    cout << "   Po usunieciu 10 (oczekiwane [30]): " << list << endl;

    // Delete tail (last element)
    toDel = list->locate(30);
    list->del(toDel);
    cout << "   Po usunieciu 30 (oczekiwane []): " << list << endl;
    cout << "   empty() (oczekiwane 1): " << list->empty() << endl;

    // 9. Test deleteX
    cout << "\n9. Test deleteX:" << endl;
    list->append(100);
    list->append(200);
    list->append(300);
    cout << "   Przed usunieciem: " << list << endl;
    
    list->deleteX(200); // Usuwanie ze środka
    cout << "   Po usunieciu 200 (oczekiwane [100, 300]): " << list << endl;
    
    list->deleteX(100); // Usuwanie z początku
    cout << "   Po usunieciu 100 (oczekiwane [300]): " << list << endl;
    
    list->deleteX(300); // Usuwanie z końca
    cout << "   Po usunieciu 300 (oczekiwane []): " << list << endl;
    
    // 10. Test deleteX elementu nieistniejącego
    cout << "\n10. Test deleteX (nieistniejacy):" << endl;
    list->append(50);
    list->deleteX(999);
    cout << "   Po probie usuniecia 999 (oczekiwane [50]): " << list << endl;

    delete list;
    return 0;
}