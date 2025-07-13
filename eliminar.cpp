#include "vehiculos.h"
using namespace std;

extern vector<Vehiculo> listaVehiculos; 

void eliminar() {
    cout << "=== ELIMINAR VEHÍCULO ===" << endl;

    int idEliminar;
    cout << "Ingrese el ID del vehículo que desea eliminar: ";
    cin >> idEliminar;

 
    auto it = find_if(listaVehiculos.begin(), listaVehiculos.end(), 
                      [idEliminar](const Vehiculo& v) { return v.id == idEliminar; });

    if (it != listaVehiculos.end()) {
      
        listaVehiculos.erase(it);
        cout << "Vehículo con ID " << idEliminar << " eliminado exitosamente." << endl;
    } else {
      
        cout << "No se encontró un vehículo con ese ID." << endl;
    }
}
