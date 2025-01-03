//Implementa Quicksort para ordenar una lista de cadenas de texto por longitud.
#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct Palabra {
	string texto;
	int longitud;
};


void quicksort(vector<Palabra>& palabras, int bajo, int alto) {//Bajo:Primera posicion | Alto: El Tamaño del vector menos 1
	if (bajo < alto) {     // Caso base: Si el índice bajo es mayor o igual al índice alto, no hay nada que ordenar.
		int pivote = palabras[alto].longitud;//[2,7],[8,1,9]
		int i = bajo - 1;                   // [0,1,][2,3,4]
		
		for (int j = bajo; j < alto; ++j) {
			if (palabras[j].longitud <= pivote) {//La Division de sub arreglos se hace mediante indices 
				++i;
				swap(palabras[i], palabras[j]);
			}
		}
		swap(palabras[i + 1], palabras[alto]);
		int indicePivote = i + 1;
		              //Los elementos menores se organizan a la izquierda y los mayores a la derecha
		quicksort(palabras, bajo, indicePivote - 1);// Subarreglo izquierdo
		quicksort(palabras, indicePivote + 1, alto);// Subarreglo derecho
	}
}

int main() {
	int size;
	cout << "Ingrese la cantidad de palabras: ";
	cin >> size;
	
	vector<Palabra> palabras(size);
	for (int i = 0; i < size; ++i) {
		cout << "Ingrese la palabra " << i + 1 << ": ";
		cin >> palabras[i].texto;
		palabras[i].longitud = palabras[i].texto.size();
	}
	
	cout << "\nLista original:\n";
	for (const auto& palabra : palabras) {
		cout << palabra.texto << " (" << palabra.longitud << ")\n";
	}
	
	quicksort(palabras, 0, palabras.size() - 1);
	
	cout << "\nLista ordenada por longitud:\n";
	for (const auto& palabra : palabras) {
		cout << palabra.texto << " (" << palabra.longitud << ")\n";
	}
	
	return 0;
}