#include <iostream>

using namespace std;
class ArrayStack{
    private:
        int* items;
        int capacity;        //pojemność stosu
        int top;                //wierzchołek stosu
    public:
        ArrayStack(int c){
            this->items = new int[c];
            this->top = -1;
            this->capacity = c;
        };    //tworzy pusty stos o pojemności c
        bool empty();
        bool full();
        void push(int x);   //wstawia daną na stos
        int peek();            //zwraca daną ze stosu
        void pop();            //usuwa daną ze stosu
        void clear();       //usuwa wszystkie elementy ze stosu
        friend std::ostream& operator<<(std::ostream& out, ArrayStack& s);    //wyświetla całą zawartość stosu
        ~ArrayStack();
};

bool ArrayStack::empty(){
    return top == -1;
}
bool ArrayStack:: full(){
    if(this->top == capacity-1){
        return true;
    }
    return false;
}

void ArrayStack::push(int x){
    if(this->top == capacity - 1){
        cout<<"Stack overflow \n";
        return;
    }    
    this->top++;

    this->items[top] = x;
}
int ArrayStack::peek(){
    return this->items[top];
}

void ArrayStack::pop(){
    if(empty()){
        cout<<"empty array";
        return;
    }
    this->top--;
}

void ArrayStack::clear(){
    while(empty() == false){
        pop();
    }
}

ostream& operator<<(ostream& out, ArrayStack& s){
    for(int i = s.top; i >= 0; i-- ){
        out << s.items[i] << " ";
    }
    return out;
}

ArrayStack::~ArrayStack(){
    delete[] items;
}

int main(){
    ArrayStack s(6);
    cout<<endl<<"empty(): 1 - "<<s.empty();
    cout<<endl<<"push(4): 4- "; s.push(4); cout<<" "<<s;
    cout<<endl<<"push(2): 2- "; s.push(2); cout<<" "<<s;
    cout<<endl<<"push(7): 7- "; s.push(7); cout<<" "<<s;
    cout<<endl<<"peek()" << s.peek(); cout<<" "<<s;
    s.pop();
    cout<<endl<<"peek()" << s.peek(); cout<<" "<<s;
    cout<<endl<<"full()" << s.full(); cout<<" "<<s;
    s.clear();
    cout<<s;
    return 0;
}