#include <iostream>

using namespace std;

int linearSearch(int needle, int haystackSize, int *haystack)
{
    if (needle == haystack[0])
    {
        return 0;
    }
    else if (needle == haystack[haystackSize - 1]){
        return haystackSize -1;
    }
    for (int i = 0; i<haystackSize; i++){
        if(haystack[i] == needle){
            return i;
        }
    }
    return -1;
}

int linearSearch2(int needle, int haystackSize, int *haystack)
{
    int counter = 0;
    if (needle == haystack[0])
    {
        return 1;
    }
    else if (needle == haystack[haystackSize - 1]){
        return 1; 
    }
    for (int i = 0; i<haystackSize; i++){
        counter++;
        if(haystack[i] == needle){
            return counter;
        }
    }
    return -1;
}
int main()
{
    int haystackSize = 6;
    int *haystack = new int[haystackSize]{5, 2, 1, 6, 2, 4};
    int needle;

    needle = 5;
    cout << endl
         << "Przypadek 1 x jest na pozycji pierwszej " << linearSearch(needle, haystackSize, haystack) << endl;
    needle = 4;
    cout << endl
         << "Przypadek 2 x jest na ostatnie pozycji " << linearSearch(needle, haystackSize, haystack) << endl;
    needle = 10;
    cout << endl
         << "Przypadek 3 x nie jest nalezy do tablicy " << linearSearch(needle, haystackSize, haystack) << endl;
    needle = 6;
    cout << endl
         << "Przypadek 4 x nalezy do tablicy " << linearSearch(needle, haystackSize, haystack) << endl;

    needle = 5;
    cout << endl
         << "Przypadek 1 x jest na pozycji pierwszej " << linearSearch2(needle, haystackSize, haystack) << endl;
    needle = 4;
    cout << endl
         << "Przypadek 2 x jest na ostatnie pozycji " << linearSearch2(needle, haystackSize, haystack) << endl;
    needle = 10;
    cout << endl
         << "Przypadek 3 x nie jest nalezy do tablicy " << linearSearch2(needle, haystackSize, haystack) << endl;
    needle = 6;
    cout << endl
         << "Przypadek 4 x nalezy do tablicy " << linearSearch2(needle, haystackSize, haystack) << endl;
    return 0;
}