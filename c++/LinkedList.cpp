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
    int getValue() { return v; };                 // zwraca wartość
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
    Element *getFirst()
    {
        return this->head;
    }; // zwraca pozycję (wskaźnik do) pierwszego elementu listy
    Element *getLast()
    {
        return this->tail;
    }; // zwraca pozycję (wskaźnik do) ostatniego elementu listy
    Element *getNext(Element *p)
    {
        if (p)
        {
            return p->getNext();
        }
        else
        {
            return nullptr;
        }
    }; // zwraca pozycję (wskaźnik do) następnego elementu listy
    Element *getPrev(Element *p)
    {
        if (p)
        {

            return p->getPrev();
        }
        else
        {
            return nullptr;
        }
    }; // zwraca pozycję (wskaźnik do) poprzedniego elementu listy
    int retrieve(Element *p)
    {
        if (p)
        {
            return p->getValue();
        }
        else
        {
            return 0;
        }
    }; // zwraca element (wartość) z pozycji (wskazywanej przez) p
    void append(int x)
    {
        Element *dot = new Element(x, nullptr, nullptr);
        if (empty())
        {
            this->head = dot;
            this->tail = dot;
            this->size++;
        }
        else
        {
            this->tail->setNext(dot);
            dot->setPrev(tail);
            this->tail = dot;
            this->size++;
        }
    }; // wstawia element z x na końcu listy
    void prepend(int x)
    {
        Element *dot = new Element(x, nullptr, nullptr);
        if (empty())
        {
            this->head = dot;
            this->tail = dot;
            this->size++;
        }
        else
        {
            this->head->setPrev(dot);
            dot->setNext(head);
            this->head = dot;
            this->size++;
        }
    }; // wstawia element z x na początku listy
    friend ostream &operator<<(ostream &out, LinkedList *l)
    {
        Element *curr = l->head;
        out << "[";
        while (curr != nullptr)
        {
            out << curr->getValue();
            if (curr->getNext() != nullptr)
            {
                out << ", ";
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
            curr = curr->getNext();
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
    void insert(Element *p, int x){
        if (!p) return;
        Element* dot = new Element(x, p->getNext(), p);
        if (p->getNext()) {
            p->getNext()->setPrev(dot);
        } else {
            this->tail = dot;
        }
        p->setNext(dot);
        this->size++;
    }; // wstawia element z wartością x na pozycję (wskazywaną przez) p (jako następnik)
    void del(Element *p){
        if (!p) return;
        
        if (p->getPrev()) {
            p->getPrev()->setNext(p->getNext());
        } else {
            this->head = p->getNext();
        }

        if (p->getNext()) {
            p->getNext()->setPrev(p->getPrev());
        } else {
            this->tail = p->getPrev();
        }

        delete p;
        this->size--;
    };           // usuwa element z pozycji (wskazywanej przez) p
    void deleteX(int x){
        Element* curr = head;
        while (curr != nullptr){
            if(curr->getValue() == x){
                del(curr);
                return; // Return immediately after deleting to avoid use-after-free
            }
            curr = curr->getNext();
        }
    };            // usuwa pierwsze wystąpienie elementu o wartości x
    ~LinkedList()
    {
        clear();
    };
};

int main()
{
    LinkedList *list = new LinkedList();

    list->append(10);
    list->prepend(5);
    list->append(20);

    // Operator<< takes a pointer, so we pass 'list' directly
    cout << list << endl;

    Element *e = list->locate(10);
    if (e)
    {
        cout << "Found element: " << list->retrieve(e) << endl;
    }

    delete list;
    return 0;
