class Element{
    private:
        int v;
        Element* next;
    public:
        Element(int x, Element* next);
        int getValue();
        Element* getNext();
        void setNext(Element* p);
};

class LinkedStack{
    private:
        Element* top;
    public:
        LinkedStack();        //tworzy pusty stos
        bool empty();
        void push(int x);  //wstawia daną na stos
        int peek();            //zwraca daną ze stosu
        void pop();            //usuwa element ze stosu
        void clear();       //usuwa wszystkie elementy ze stosu
        friend std::ostream& operator<<(std::ostream& out, LinkedStack* s); //wyświetla zawartość całego stosu
        ~LinkedStack();
};

//Zadanie 2 - przykładowy sposób testowania
LinkedStack* s = new LinkedStack();
cout<<endl<<"empty(): 1 - "<<s->empty();
cout<<endl<<"push(4): 4- "; s->push(4); cout<<" "<<s;
//...

