/*
Implementa  una función de comparación 
personalizada (por ejemplo, mayor o menor) para usar en el algoritmo de inserción.

*/


#include <iostream>
using namespace std;

// Prototipos de funciones
void insertionSort(int arr[], int size, int opcion);
int menuInsert();

int main() {
    int size = 0;

    cout << "Ingresa el tamaño del arreglo: ";
    cin >> size;

    int arr[size];
    cout << "Ingresa los elementos del arreglo: " << endl;
    for (int i = 0; i < size; i++) {
        cout << "Elemento " << i + 1 << ": ";
        cin >> arr[i];
    }

    int opcion = menuInsert();

    // Validar la opción
    if (opcion != 1 && opcion != 2) {
        cout << "Opción no válida." << endl;
        return 1;
    }

    insertionSort(arr, size, opcion);

    cout << "Arreglo ordenado: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}



int menuInsert() {
    int opcion;
    cout << "Elige el tipo de ordenamiento: " << endl;
    cout << "1. Menor a Mayor" << endl;
    cout << "2. Mayor a Menor" << endl;
    cout << "Opción: ";
    cin >> opcion;
    return opcion;
}

void insertionSort(int arr[], int size, int opcion) {
    for (int i = 1; i < size; i++) {
        int actual = arr[i];
        int j = i - 1;

        switch (opcion) {
            case 1: // Menor a mayor
                while (j >= 0 && arr[j] > actual) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                break;

            case 2: // Mayor a menor
                while (j >= 0 && arr[j] < actual) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                break;
        }

        arr[j + 1] = actual;

        cout << "Recorrido " << i << ": ";
        for (int k = 0; k < size; k++) {
            cout << arr[k] << " ";
        }
        cout << endl;
    }
}
