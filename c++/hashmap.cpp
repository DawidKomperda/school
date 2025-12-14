#include <iostream>

using namespace std;

class HashTable
{
private:
    string *t;
    int capacity;
    int size;

public:
    HashTable(int c)
    {
        this->capacity = c;
        this->size = 0;
        this->t = new string[c];
    }; // konstruktor tworzący pustą tablicę o pojemności c
    bool empty() { return this->size == 0; };
    bool full() { return this->size == this->capacity; };
    int hashFunction(string s)
    {
        unsigned long hash = 0;
        int p = 31;

        for (int i = 0; i < s.length(); i++)
        {
            hash = (hash * p + s[i]);
        }
        return hash % capacity;
    }; // funkcja haszująca dla klucza s
    void insert(string d)
    {
        if (full())
        {
            cout << "its' full"<<endl;
            return;
        }
        int place = this->hashFunction(d);

        while (t[place] != "" && t[place] != "_DEL_")
        {
            place++;
            if (place == capacity)
            {
                place = 0;
            }
        }

        t[place] = d;
        this->size++;

    }; // wstawienie danych d z kluczem s (tutaj d=s)
    void del(string s)
    {
        int check = this->hashFunction(s);
        int startPlace = check;

        while (t[check] != "")
        {
            if (t[check] == s)
            {
                t[check] = "_DEL_";
                this->size--;
                return;
            }
            check++;

            if (check == capacity)
                check = 0;
            if (check == startPlace)
                break;
        }
    }; // usuwa dane z kluczem s
    string search(string s)
    {
        int check = this->hashFunction(s);
        int startPlace = check;

        while (t[check] != "")
        {
            if (t[check] == s)
            {
                return t[check];
            }
            check++;

            if (check == capacity)
            {
                check = 0;
            }
            if (check == startPlace)
            {
                break;
            }
        }
        return "";
    }; // wyszukuje i zwraca dane z s
    friend ostream &operator<<(ostream &out, HashTable &ht)
    {
        out << "Hash Map:" << endl;
        for (int i = 0; i < ht.capacity; i++)
        {
            out << "[" << i << "]: ";
            if (ht.t[i] != "")
            {
                out << ht.t[i];
            }
            out << endl;
        }
        return out;
    }; // wypisuje tablicę (z numerami pól), pozostawia puste dla wolnych pól
};

int main(int argc, char **argv)
{

    // Zadanie 1 - test
    cout << "Zadanie 1 - test" << endl;
    int n = 10; // pojemność tablicy z haszowaniem
    HashTable h(n);
    cout << "Test 1 Insert";
    h.insert("siema");
    h.insert("bonjour");
    h.insert("slon");
    h.insert("matko");
    cout << h;
    cout << h.search("slon");
    h.del("bonjour");
    cout << h;
    h.insert("taada");
    h.insert("taada");
    h.insert("taada");
    h.insert("taada");
    h.insert("taada");
    h.insert("taada");
    h.insert("taada");
    cout << h;
    h.insert("taada");
    h.insert("taada");
    cout << h;
    return 0;
}