#include <iostream>

using namespace std;

class Heap{
    private:
        int* kopiec;
        int capacity;
        int size;
    public:
        Heap(int c);            
        bool empty();
        bool full();
        void bottomUp(int i);                
        void topDown(int i);                
        void insert(int x);                    
        void deleteP();                       
        void del(int i);                         
        friend std::ostream& operator<<(std::ostream& out, Heap& h);

};


Heap::Heap(int c){
    this->capacity = c;
    this->size = 0;         
    this->kopiec = new int[c]; 
}

bool Heap::empty(){
    return size == 0; 
}

bool Heap::full(){
    return size == capacity; 
}  

void Heap::bottomUp(int i){
    int parent = (i - 1) / 2;
    
    while (i > 0 && kopiec[i] > kopiec[parent]) {
        swap(kopiec[i], kopiec[parent]);
        
        i = parent;
        parent = (i - 1) / 2;
    }
}

void Heap::topDown(int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && kopiec[left] > kopiec[largest])
        largest = left;

    if (right < size && kopiec[right] > kopiec[largest])
        largest = right;

    if (largest != i) {
        swap(kopiec[i], kopiec[largest]);
        topDown(largest);
    }
}

void Heap::insert(int x) {
    if (full()) {
        cout << "Heap is full!" << endl;
        return;
    }
    
    kopiec[size] = x;
    size++;
    
    bottomUp(size - 1);
}

void Heap::deleteP(){
    if(empty()){
        cout << "Heap is empty!" << endl;
        return;
    }
    
    kopiec[0] = kopiec[size - 1];
    size--;
    
    if(size > 0) {
        topDown(0);
    }
}

void Heap::del(int i){
    if(i < 0 || i >= size){
        cout << "Index out of bounds!" << endl;
        return;
    }
    
    kopiec[i] = kopiec[size - 1];
    size--;
    
    if(i > 0 && kopiec[i] > kopiec[(i-1)/2]){
        bottomUp(i);
    } 
    else {
        topDown(i);
    }
}

std::ostream& operator<<(std::ostream& out, Heap& h) {
    out << "[ ";
    for (int i = 0; i < h.size; i++) {
        out << h.kopiec[i] << " ";
    }
    out << "]";
    return out;
}

int main(){ 
    cout << "--- HEAP TEST ---" << endl;
    
    Heap h(10);
    
    h.insert(10);
    h.insert(20); 
    h.insert(5);
    h.insert(30);
    h.insert(15);
    
    cout << "Initial Heap: " << h << endl;

    cout << "\n--- Testing deleteP (Delete Max) ---" << endl;
    h.deleteP(); 
    cout << "After deleteP(): " << h << endl;

    cout << "\n--- Testing del(int i) ---" << endl;
    cout << "Deleting index 2 (value 5)..." << endl;
    h.del(2);
    cout << "After del(2):    " << h << endl;

    cout << "\n--- Testing del with bottomUp trigger ---" << endl;
    h.insert(50); 
    cout << "Inserted 50:     " << h << endl;
    
    h.del(1);
    cout << "After del(1):    " << h << endl;
    
    return 0;
}