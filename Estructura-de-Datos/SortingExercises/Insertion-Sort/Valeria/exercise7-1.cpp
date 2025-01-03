/*
Implementa una función que acepte una lista y una función de comparación 
personalizada (por ejemplo, mayor o menor) para usar en el algoritmo de inserción.
*/

#include <iostream>
using namespace std;

// Definición de la estructura Nodo
struct Nodo {
    int dato;          // Valor almacenado en el nodo
    Nodo* siguiente;   // Puntero al siguiente nodo
};

// Prototipos de funciones
void insertarNodo(Nodo*& cabeza, int valor);
void imprimirLista(Nodo* cabeza);
void insertionSort(Nodo*& cabeza, int opcion);

int main() {
    Nodo* lista = nullptr; // Inicializar lista vacía
    int num, valor, opcion;

    cout << "¿Cuántos números deseas almacenar en la lista?: ";
    cin >> num;

    // Insertar los números en la lista
    for (int i = 0; i < num; i++) {
        cout << "Ingresa el número " << i + 1 << ": ";
        cin >> valor;
        insertarNodo(lista, valor);
    }

    // Mostrar el menú para elegir el tipo de ordenamiento
    cout << "Elige el tipo de ordenamiento: " << endl;
    cout << "1. Menor a Mayor" << endl;
    cout << "2. Mayor a Menor" << endl;
    cout << "Opción: ";
    cin >> opcion;


    insertionSort(lista, opcion);

    // Imprimir la lista ordenada
    cout << "Lista ordenada: ";
    imprimirLista(lista);

    return 0;
}

// Función para insertar un nodo al final de la lista
void insertarNodo(Nodo*& cabeza, int valor) {
    Nodo* nuevoNodo = new Nodo(); // Crear un nuevo nodo
    nuevoNodo->dato = valor;      // Asignar el valor al nuevo nodo
    nuevoNodo->siguiente = nullptr; // El nuevo nodo apunta a nullptr

    if (cabeza == nullptr) { // Si la lista está vacía
        cabeza = nuevoNodo; // El nuevo nodo es la cabeza
    } else {
        Nodo* aux = cabeza; // Crear un nodo auxiliar que apunte a la cabeza
        while (aux->siguiente != nullptr) { // Recorrer la lista hasta el último nodo
            aux = aux->siguiente;
        }
        aux->siguiente = nuevoNodo; // El último nodo apunta al nuevo nodo
    }
}

void imprimirLista(Nodo* cabeza) {
    Nodo* aux = cabeza; // Crear un nodo auxiliar que apunte a la cabeza
    while (aux != nullptr) { // Recorrer la lista hasta llegar al final
        cout << aux->dato << " ";
        aux = aux->siguiente;
    }
    cout << "nullptr" << endl;
}

// Función para ordenar la lista enlazada usando el algoritmo de inserción
void insertionSort(Nodo*& cabeza, int opcion) {
    if (cabeza == nullptr || cabeza->siguiente == nullptr) {
        return; // No hay nada que ordenar si la lista tiene 0 o 1 nodo
    }

    Nodo* sorted = nullptr; // Lista ordenada

    while (cabeza != nullptr) {
        Nodo* actual = cabeza; // Extraer el nodo actual de la lista original
        cabeza = cabeza->siguiente; // Mover la cabeza al siguiente nodo

        // Insertar el nodo actual en la posición correcta de la lista ordenada
        if (sorted == nullptr || 
            (opcion == 1 && sorted->dato > actual->dato) || 
            (opcion == 2 && sorted->dato < actual->dato)) {
            // Insertar al principio si la lista ordenada está vacía
            // o el nodo actual debe ser el nuevo primero
            actual->siguiente = sorted;
            sorted = actual;
        } else {
            // Buscar la posición correcta en la lista ordenada
            Nodo* aux = sorted;
            while (aux->siguiente != nullptr &&
                   ((opcion == 1 && aux->siguiente->dato <= actual->dato) ||
                    (opcion == 2 && aux->siguiente->dato >= actual->dato))) {
                aux = aux->siguiente;
            }
            actual->siguiente = aux->siguiente;
            aux->siguiente = actual;
        }
    }

    cabeza = sorted; // Actualizar la cabeza con la lista ordenada
}
