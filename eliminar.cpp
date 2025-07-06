#include <iostream>
#include <string>
#include <vector>
#include <clocale>
using namespace std;

//CREACION DE CRUD AUTOS

struct vehiculos{
    int id;
    string marca;
    string modelo;
    int año;
    double precio; 
    int cantidad;
};

vector<vehiculos> listaVehiculos;
vector<vehiculos> leer() {
    return listaVehiculos;
}

int contadorID = 1;

// Función para agregar un vehículo
void agregar() {
    vehiculos nuevo;
    nuevo.id = contadorID++;

    cout << "Marca: ";
    getline(cin, nuevo.marca);
    cout << "Modelo: ";
    getline(cin, nuevo.modelo);

    while (true) {
        cout << "Año: ";
        cin >> nuevo.año;
        if (nuevo.año >= 1950 && nuevo.año <= 2025) {
            break;
        } else {
            cout << "Año ingresado invalido (SOLO AUTOS ENTRE 1950 Y 2025)" << endl;
        }
    }
