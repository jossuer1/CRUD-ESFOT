#ifndef VEHICULOS_H
#define VEHICULOS_H

#include <string>
#include <vector>
using namespace std;

struct Vehiculo {
    int id;
    string marca;
    string modelo;
    int año;
    double precio;
    int cantidad;
};

extern vector<Vehiculo> listaVehiculos;
extern int contadorID;

#endif // VEHICULOS_H
