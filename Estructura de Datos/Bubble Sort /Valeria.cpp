/*
Ordena una lista de estructuras con dos campos: nombre y edad, basándote en la 
edad. 
*/

#include <iostream>
using namespace std;

struct Persona{
    string nombre;
    int edad;
};

void mostrarDatos(Persona personas);
void metodoBurbuja(Persona personas[], int size);

int main() {
    
    int size;
    cout<<"Introduce el numero de personas: ";
    cin>>size;

    cin.ignore();

    //Crear el arreglo de personas con el tamaño
    Persona personas[size];

    //Llenar el arreglo de personas
    for(int i = 0; i < size; i++){

        cout<<"Nombre de la persona "<<i+1<<": ";
        getline(cin, personas[i].nombre); //Acceder a cada persona

        cout<<"Edad de la persona "<<i+1<<": ";
        cin>>personas[i].edad;
        cout<<endl;

        //Limpiar buffer 
        cin.ignore();
    }

    //mostrar arreglo antes de ordenar
    cout<<"ARREGLO ANTES DE ORDENAR: "<<endl;
    for(int i = 0; i < size; i++){
        mostrarDatos(personas[i]);
        cout<<endl;
    }

    //Ordenar el arreglo de personas
    metodoBurbuja(personas, size);

    cout<<endl;

    //mostrar arreglo antes de ordenar
    cout<<"ARREGLO DESPUÉS DE ORDENAR: "<<endl;
    for(int i = 0; i < size; i++){
        mostrarDatos(personas[i]);
        cout<<endl;
    }

    
    return 0;
}



void mostrarDatos(Persona personas){
    cout<< "Nombre: "<< personas.nombre<<endl;
    cout<< "Edad: "<< personas.edad<<endl;
}

void metodoBurbuja(Persona personas[], int size){
    for( int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if (personas[j].edad > personas[j+1].edad){
                swap(personas[j], personas[j+1]);
            }
        }
    }

}

