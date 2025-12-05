#include <iostream>

using namespace std;

void print(int *S, int n)
{ // wyświetla dane
    for (int i = 0; i < n; i++)
    {
        cout << S[i] << endl;
    }
}
void init(int *S, int n)
{ // generuje losowe dane
}
void insertionSort(int *S, int n)
{
    for (int i = 0; i < n; i++)
    {
        int key = S[i];
        int j = i - 1;

        while (j>=0 && S[j] > key)
        {
            S[j + 1] = S[j];
            j = j - 1;
        }
        S[j + 1] = key;
    }
}
void selectionSort(int *S, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        int minIndex = i; 
        
        for (int j = i+1; j < n; j++){
            if (S[j] < S[minIndex]){
                minIndex = j; 
            }
        }
        
        swap(S[i], S[minIndex]);
    }
}
void bubbleSort(int *S, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp;
            if (S[j] > S[j + 1])
            {
                temp = S[j];
                S[j] = S[j + 1];
                S[j + 1] = temp;
            }
        }
    }
}

int main()
{

    // Zadanie 1 - test
    cout << "Zadanie 1 - test - sortowanie ..." << endl;

    int S[20]{4, 1, 56, 2, 1, 6, 13, 5, 9, 3, 4, 56, 16, 56, 10, 5};

    // bubbleSort(S, 20);
    // insertionSort(S,20);
    selectionSort(S, 20);

    print(S, 20);
}
