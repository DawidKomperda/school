#include <iostream>
#include <cstdlib>

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

    // int haystackSize = 6;
    // int *haystack = new int[haystackSize]{1, 2, 3, 5, 6, 7};
    // int needle;

    // needle = 1;
    // cout << endl
    //      << "Przypadek 1 x jest na pozycji pierwszej " << binarySearch(needle, haystackSize, haystack) << endl;
    // needle = 7;
    // cout << endl
    //      << "Przypadek 2 x jest na ostatnie pozycji " << binarySearch(needle, haystackSize, haystack) << endl;
    // needle = 10;
    // cout << endl
    //      << "Przypadek 3 x nie jest nalezy do tablicy " << binarySearch(needle, haystackSize, haystack) << endl;
    // needle = 6;
    // cout << endl
    //      << "Przypadek 4 x nalezy do tablicy " << binarySearch(needle, haystackSize, haystack) << endl;
    

    // needle = 1;
    // cout << endl
    //      << "Przypadek 1 x jest na pozycji pierwszej " << binarySearch2(needle, haystackSize, haystack) << endl;
    // needle = 7;
    // cout << endl
    //      << "Przypadek 2 x jest na ostatnie pozycji " << binarySearch2(needle, haystackSize, haystack) << endl;
    // needle = 10;
    // cout << endl
    //      << "Przypadek 3 x nie jest nalezy do tablicy " << binarySearch2(needle, haystackSize, haystack) << endl;
    // needle = 6;
    // cout << endl
    //      << "Przypadek 4 x nalezy do tablicy " << binarySearch2(needle, haystackSize, haystack) << endl;


    // needle = 5;
    // cout << endl
    //      << "Przypadek 1 x jest na pozycji pierwszej " << linearSearch(needle, haystackSize, haystack) << endl;
    // needle = 4;
    // cout << endl
    //      << "Przypadek 2 x jest na ostatnie pozycji " << linearSearch(needle, haystackSize, haystack) << endl;
    // needle = 10;
    // cout << endl
    //      << "Przypadek 3 x nie jest nalezy do tablicy " << linearSearch(needle, haystackSize, haystack) << endl;
    // needle = 6;
    // cout << endl
    //      << "Przypadek 4 x nalezy do tablicy " << linearSearch(needle, haystackSize, haystack) << endl;

    // needle = 5;
    // cout << endl
    //      << "Przypadek 1 x jest na pozycji pierwszej " << linearSearch2(needle, haystackSize, haystack) << endl;
    // needle = 4;
    // cout << endl
    //      << "Przypadek 2 x jest na ostatnie pozycji " << linearSearch2(needle, haystackSize, haystack) << endl;
    // needle = 10;
    // cout << endl
    //      << "Przypadek 3 x nie jest nalezy do tablicy " << linearSearch2(needle, haystackSize, haystack) << endl;
    // needle = 6;
    // cout << endl
    //      << "Przypadek 4 x nalezy do tablicy " << linearSearch2(needle, haystackSize, haystack) << endl;
    
    int random;
    int haystackSize;
    int *haystack = new int[haystackSize]{};
    int needle;
    
    random = rand()%10;
    random = rand()%100;
    random = rand()%1000;
    random = rand()%10000;
        
    // To do later
    return 0;
}
