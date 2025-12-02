#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    
    int n;
    cin >> n;
    
    int* array = new int[n];
    
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 100;
    }
    
    cout << "\nArray:" << endl;
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    
    cout << "\nAddres " << array << endl;
    
    for (int i = 0; i < n; i++) {
        cout << i << ": " << (char*)&array[i] - (char*)array << " , " << &array[i] << endl;    
    }
    
    delete[] array;
    
    return 0;
}
