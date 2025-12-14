#include <iostream>
#include <string>

using namespace std;

void naiveStringMatching(string T, string p) {
    int n = T.length(); 
    int m = p.length();

    if (m > n) {
        cout << "Błąd: Wzorzec jest dłuższy niż tekst." << endl;
        return;
    }

    bool found = false;
    for( int i = 0; i<= n-m ;i++){
        int j;
        for ( j = 0; j < m;j++){
            if(T[i+j] != p[j]){
                break;
            }
        }
        
        if( j == m ){
            cout <<"znaleziono na pozycji " << i << endl;
            found = true;
        }
        if (!found) {
            cout << "Nie znaleziono wzorca w tekście." << endl;
            break;
        }
    }
}

int main() {
    // Zadanie 1 - testy

    cout << "--- TEST 1: Przykład złożony ---" << endl;
    string text1 = "gfrgfgigjmgfrrogirgfrgfrgfrgirhgrygfrgfygirmggfrgfgfrgffeutyitbhfuvwgfrgf";
    string pattern1 = "gfrgf";
    
    cout << "Tekst: " << text1 << endl;
    cout << "Wzorzec: " << pattern1 << endl;
    naiveStringMatching(text1, pattern1);
    cout << endl;

    cout << "--- TEST 2: Wzorzec na początku, w środku i na końcu ---" << endl;
    string text2 = "ABrakadABraAB";
    string pattern2 = "AB";
    
    cout << "Tekst: " << text2 << endl;
    cout << "Wzorzec: " << pattern2 << endl;
    naiveStringMatching(text2, pattern2);
    cout << endl;

    cout << "--- TEST 3: Brak wystąpień ---" << endl;
    string text3 = "Szukajcie a znajdziecie";
    string pattern3 = "nie ma mnie";
    
    cout << "Tekst: " << text3 << endl;
    cout << "Wzorzec: " << pattern3 << endl;
    naiveStringMatching(text3, pattern3);

    return 0;
}