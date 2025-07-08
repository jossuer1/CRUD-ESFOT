#include <iostream>
#include <string>
#include <vector>
#include <clocale>
using namespace std;

struct vehiculos{
    int id;
    string marca;
    string modelo;
    int año;
    double precio; 
	int cantidad;

};
vector<vehiculos>listaVehiculos;



void actualizar(){
    int idAuto;
    cout << "Ingrese el ID del vehículo a actualizar: ";
    cin >> idAuto;
    cin.ignore();

    bool encontrado = false;

    for (auto& v : listaVehiculos) {
        if (v.id == idAuto) {
            encontrado = true;
            cout << "Vehículo encontrado"<<endl;
			cout <<" Datos actuales ";<<endl;
            cout << "Marca: " << v.marca << endl;
            cout << "Modelo: " << v.modelo << endl;
            cout << "Año: " << v.año << endl;
            cout << "Precio: $" << v.precio << endl;
            cout << "Cantidad: " << v.cantidad << endl;

            string opcion;

            cout << "¿Desea modificar la marca? (s/n): ";
            getline(cin, opcion);
            if (opcion == "s" || opcion == "S") {
                cout << "Nueva marca: ";
                getline(cin, v.marca);
            }

            cout << "¿Desea modificar el modelo? (s/n): ";
            getline(cin, opcion);
            if (opcion == "s" || opcion == "S") {
                cout << "Nuevo modelo: ";
                getline(cin, v.modelo);
            }

            while (true) {
                cout << "¿Desea modificar el año? (s/n): ";
                getline(cin, opcion);
                if (opcion == "s" || opcion == "S") {
                    cout << "Nuevo año: ";
                    cin >> v.año;
                    cin.ignore();
                    if (v.año >= 1950 && v.año <= 2025) {
                        break;
                    } else {
                        cout << "Año ingresado inválido (SOLO AUTOS ENTRE 1950 Y 2025)" << endl;
                    }
                } else {
                    break;
                }
            }

            cout << "¿Desea modificar el precio? (s/n): ";
            getline(cin, opcion);
            if (opcion == "s" || opcion == "S") {
                cout << "Nuevo precio: ";
                cin >> v.precio;
                cin.ignore();
            }

            cout << "Vehículo actualizado con éxito.\n";
            return;
        }
    }

    if (!encontrado) {
        cout << "No se encontró ningún vehículo con el ID ingresado.\n";
    }
}
