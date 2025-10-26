#include <iostream>

using namespace std;

int binarySearch (int needle, int haystacksize, int *haystack){
    
    if(needle == haystack[0]){
        return 0;
    }
    else if (needle == haystack[haystacksize-1]){
        return haystacksize-1;
    }
    int low = 0;
    int high = haystacksize-1;
    while(low <= high){
        int mid = (low+high)/2;
        if (haystack[mid] == needle){
            return mid;
        }
        else if (haystack[mid] > needle){
            high = mid;
        }
        else{
            low = mid+1;
        }
    }
    return -1;

}
    
int binarySearch2 (int needle, int haystacksize, int *haystack){
    
    if(needle == haystack[0]){
        return 1;
    }
    else if (needle == haystack[haystacksize-1]){
        return 1;
    }
    int counter = 0;
    int low = 0;
    int high = haystacksize-1;
    while(low <= high){
        counter++;
        int mid = (low+high)/2;
        if (haystack[mid] == needle){
            return counter;
        }
        else if (haystack[mid] > needle){
            high = mid;
        }
        else{
            low = mid+1;
        }
    }
    return -1;

}

int main(){

    int haystackSize = 6;
    int *haystack = new int[haystackSize]{1, 2, 3, 5, 6, 7};
    int needle;

    needle = 1;
    cout << endl
         << "Przypadek 1 x jest na pozycji pierwszej " << binarySearch(needle, haystackSize, haystack) << endl;
    needle = 7;
    cout << endl
         << "Przypadek 2 x jest na ostatnie pozycji " << binarySearch(needle, haystackSize, haystack) << endl;
    needle = 10;
    cout << endl
         << "Przypadek 3 x nie jest nalezy do tablicy " << binarySearch(needle, haystackSize, haystack) << endl;
    needle = 6;
    cout << endl
         << "Przypadek 4 x nalezy do tablicy " << binarySearch(needle, haystackSize, haystack) << endl;
    

    needle = 1;
    cout << endl
         << "Przypadek 1 x jest na pozycji pierwszej " << binarySearch2(needle, haystackSize, haystack) << endl;
    needle = 7;
    cout << endl
         << "Przypadek 2 x jest na ostatnie pozycji " << binarySearch2(needle, haystackSize, haystack) << endl;
    needle = 10;
    cout << endl
         << "Przypadek 3 x nie jest nalezy do tablicy " << binarySearch2(needle, haystackSize, haystack) << endl;
    needle = 6;
    cout << endl
         << "Przypadek 4 x nalezy do tablicy " << binarySearch2(needle, haystackSize, haystack) << endl;

    return 0;
}