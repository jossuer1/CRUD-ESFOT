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
	cout<<"Ingres el id del auto que desea actualizar: ";
	cin >> idAuto;
	cin.ignore();
	
	for(auto &  v:listaVehiculos){
		if(v.id == idAuto){
			cout<<"Ingres la nueva Marca: ";
			getline(cin, v.marca);
			cout<<"Ingrese el nuevo Modelo: ";
			getline(cin, v.modelo);
			cout<<"Ingrese el nuevo año: ";
			cin>>v.año;
			cout<<"Ingrese el nuevo precio: ";
			cin>>v.precio;
			cin.ignore();
			
			cout<<"Datos actualizados correctamente.\n";
			return;
		}
	}
	cout<<"No se encontro un vehiculo con ese ID.\n";
	
	
}


