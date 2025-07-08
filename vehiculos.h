#ifndef VEHICULOS_H
#define VEHICULOS_H

#include <string>
using namespace std;

struct Vehiculo {
    int id;
    string marca;
    string modelo;
    int anio;
    double precio;
    int cantidad;
};

#endif // VEHICULOS_H
