// Usa Mergesort para ordenar una lista de estructuras basándote en múltiples campos
//(por ejemplo, edad y nombre).

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

struct Student
{
    int years;
    string name;
};

void merge(Student students[], int low, int mid, int high, int option);
void mergeSort(Student students[], int low, int high, int option);
void print(Student students[], int size);

int main()
{
    int size = 0;
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> size;

    Student students[size];

    for (int i = 0; i < size; i++)
    {
        cout << "\n Ingrese el nombre del estudiante " << i + 1 << ": ";
        cin.ignore();
        getline(cin, students[i].name);
        transform(students[i].name.begin(), students[i].name.end(), students[i].name.begin(), ::toupper);

        cout << " Ingrese la edad del estudiante " << i + 1 << ": ";
        cin >> students[i].years;
    }
    cout << "Registro de estudiantes guardado correctamente." << endl;

    int option = 0;

    do
    {
        cout << "\nSeleccione una opción: " << endl;
        cout << "1. Ordenar por edad" << endl;
        cout << "2. Ordenar por nombre" << endl;
        cout << "3. Salir\n"
             << endl;

        cin >> option;
        cout << endl;

        if (option != 3)
        {
            cout << "Elementos ordenados: " << endl;
            mergeSort(students, 0, size - 1, option);
            print(students, size);
        }

    } while (option != 3);

    return 0;
}

void mergeSort(Student students[], int low, int high, int option) // funcion recursiva
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergeSort(students, low, mid, option);
        mergeSort(students, mid + 1, high, option);

        merge(students, low, mid, high, option);
    }
}

void merge(Student students[], int low, int mid, int high, int option)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    Student L[n1];
    Student R[n2];

    for (int i = 0; i < n1; i++)
    {
        int s = (low + i);
        L[i] = students[s];
    }

    for (int i = 0; i < n2; i++)
    {
        int s = mid + 1 + i;
        R[i] = students[s];
    }

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2)
    {
        if (option == 1)
        {
            if (L[i].years <= R[j].years)
            {
                students[k] = L[i];
                i++;
            }
            else
            {
                students[k] = R[j];
                j++;
            }
            k++;
        }
        else if (option == 2)
        {

            if (L[i].name <= R[j].name)
            {
                students[k] = L[i];
                i++;
            }
            else
            {
                students[k] = R[j];
                j++;
            }
            k++;
        }
    }

    while (i < n1)
    {
        students[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        students[k] = R[j];
        j++;
        k++;
    }
}

void print(Student students[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << students[i].name << ", " << students[i].years << endl;
    }
}