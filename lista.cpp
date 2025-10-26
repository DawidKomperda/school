#include <iostream>

using namespace std;

class Element
{
private:
    int v;
    Element *next;
    Element *prev;

public:
    Element(int x, Element *next, Element *prev) {
        this->v = x;
        this->next = next;
        this->prev = prev;
    }
    
    int getValue();                               // zwraca wartość
    void setValue(int v);                         // ustawia warość v
    Element *getNext();                           // zwraca ozycję następnego elementu
    Element *getPrev();                           // zwraca pozycję poprzedniego elementu
    void setNext(Element *p);                     // ustawia p jako następny element
    void setPrev(Element *p);                     // ustawia p jako poprzedni element
};

class LinkedList
{
private:
    Element *head; // pozycja pierwszego elementu
    Element *tail; // pozycja ostatniego elementu
    int size;

public:
    LinkedList();                                            // tworzy pustą listę
    bool empty();                                            // zwraca prawdę jeśli lista pusta, fałsz w przeciwnym przypadku
    int getSize();                                           // zwraca wielkość listy (liczbę elementów w liście)
    Element *getFirst();                                     // zwraca pozycję (wskaźnik do) pierwszego elementu listy
    Element *getLast();                                      // zwraca pozycję (wskaźnik do) ostatniego elementu listy
    Element *getNext(Element *p);                            // zwraca pozycję (wskaźnik do) następnego elementu listy
    Element *getPrev(Element *p);                            // zwraca pozycję (wskaźnik do) poprzedniego elementu listy
    int retrive(Element *p);                                 // zwraca element (wartość) z pozycji (wskazywanej przez) p
    void append(int x);                                      // wstawia element z x na końcu listy
    void preppend(int x);                                    // wstawia element z x na początku listy
    friend ostream &operator<<(ostream &out, LinkedList *l); // wypisuje elementu listy
    Element *locate(int x);                                  // zwraca pozycję pierwszego wystąpienia elementu z x, NULL jeśli x nie występuje
    void clear();                                            // usuwa całą listę (zawartość)
    void insert(Element *p, int x);                          // wstawia element z wartością x na pozycję (wskazywaną przez) p
    void del(Element *p);                                    // usuwa element z pozycji (wskazywanej przez) p
    void deleteX(int x);                                     // usuwa pierwsze wystąpienie elementu o wartości x
    ~LinkedList();
};

LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

int Element::getValue() { return this->v; }
void Element::setValue(int v) { this->v = v; }
Element *Element::getNext() { return this->next; }
Element *Element::getPrev() { return this->prev; }
void Element::setNext(Element *p) { this->next = p; }
void Element::setPrev(Element *p) { this->prev = p; }

bool LinkedList::empty()
{
    return size == 0;
}
int LinkedList::getSize() { return size; }
Element *LinkedList::getFirst() { return this->head; }
Element *LinkedList::getLast() { return this->tail; }
Element *LinkedList::getNext(Element *p) { return p->getNext(); }
Element *LinkedList::getPrev(Element *p) { return p->getPrev(); }
int LinkedList::retrive(Element *p)
{
    return p->getValue();
}
void LinkedList::append(int x)
{
    Element *elemNew = new Element(x, nullptr, tail);
    if (empty())
    {
        this->tail = elemNew;
        this->head = elemNew;
    }
    else
    {
        this->tail->setNext(elemNew);
        this->tail = elemNew;
    }
    this->size++;
}
void LinkedList::preppend(int x)
{
    Element *elemNew = new Element(x, head, nullptr);
    if (empty())
    {
        this->head = elemNew;
        this->tail = elemNew;
    }
    else
    {
        this->head->setPrev(elemNew);
        this->head = elemNew;
    }
    this->size++;
}
ostream &operator<<(ostream &out, LinkedList *l)
{
    Element *curr = l->getFirst();
    while (curr != nullptr)
    {
        out << curr->getValue() << " ";
        curr = curr->getNext();
    }
    return out;
}
Element *LinkedList::locate(int x)
{
    Element *curr = this->head;
    while (curr != nullptr)
    {
        if (curr->getValue() == x)
        {
            return curr;
        }
        curr = curr->getNext();
    }
    return nullptr;
}
void LinkedList::clear()
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
}

void LinkedList::insert(Element *p, int x)
{
    if (p == nullptr)
    {
        return;
    }

    Element *elemNew = new Element(x, p, p->getPrev());
    
    if (p == this->head)
    {
        this->head = elemNew;
        p->setPrev(elemNew);
    }
    else
    {
        p->getPrev()->setNext(elemNew);
        p->setPrev(elemNew);
    }
    this->size++;
}

void LinkedList::del(Element *p)
{
    if (p == nullptr) return;

    if (this->size == 1)
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size--;
        delete p;
        return;
    }

    if (p == this->head)
    {
        this->head = this->head->getNext();
        this->head->setPrev(nullptr);
        this->size--;
        delete p;
        return;
    }

    if (p == this->tail)
    {
        this->tail = this->tail->getPrev();
        this->tail->setNext(nullptr);
        this->size--;
        delete p;
        return;
    }
    
    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());
    this->size--;
    delete p;
}

void LinkedList::deleteX(int x)
{
    if (empty()) return;
    
    Element *curr = this->head;

    if (this->size == 1)
    {
        if (curr->getValue() == x)
        {
            this->head = nullptr;
            this->tail = nullptr;
            this->size--;
            delete curr;
        }
        return;
    }
    
    if (this->head->getValue() == x)
    {
        Element *toDelete = this->head;
        this->head = this->head->getNext();
        this->head->setPrev(nullptr);
        this->size--;
        delete toDelete;
        return;
    }
    
    if (this->tail->getValue() == x)
    {
        Element *toDelete = this->tail;
        this->tail = this->tail->getPrev();
        this->tail->setNext(nullptr);
        this->size--;
        delete toDelete;
        return;
    }

    curr = this->head->getNext();
    while (curr != this->tail)
    {
        if (curr->getValue() == x)
        {
            curr->getPrev()->setNext(curr->getNext());
            curr->getNext()->setPrev(curr->getPrev());
            this->size--;
            delete curr;
            return;
        }
        curr = curr->getNext();
    }
}

LinkedList::~LinkedList()
{
    clear();
}

int main()
{
    LinkedList *list = new LinkedList();
    
    list->append(10);
    list->append(20);
    list->append(30);
    cout << "List: " << list << endl;
    cout << "Size: " << list->getSize() << endl;
    
    list->deleteX(20);
    cout << "After deleting 20: " << list << endl;
    cout << "Size: " << list->getSize() << endl;
    
    delete list;
    return 0;
}