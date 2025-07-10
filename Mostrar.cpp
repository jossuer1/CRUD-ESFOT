#include <iostream>
#include <string>
#include <vector>
#include "vehiculos.h"
using namespace std;

void mostrar() {
    cout << "=== INVENTARIO DE VEHÍCULOS ===" << endl;

    if (listaVehiculos.empty()) {
        cout << "No hay vehículos en el inventario." << endl;
        return;
    }

    int totalAutos = 0;

    cout << "\n===== LISTA DE VEHÍCULOS DISPONIBLES =====\n";
    cout << "ID\tMarca\tModelo\tAño\tPrecio\tCantidad" << endl;

    for (auto& v : listaVehiculos) {
        cout << v.id << "\t" << v.marca << "\t" << v.modelo 
             << "\t" << v.año << "\t$" << v.precio 
             << "\t" << v.cantidad << endl;

        totalAutos += v.cantidad;
    }
}
