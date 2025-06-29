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
};
vector<vehiculos>listaVehiculos;

vector<vehiculos> leer(){
	return listaVehiculos;
};

void agregar(const auto& autoAgregar){
	for(const auto& modelo : listaVehiculos){
		if(modelo.id == autoAgregar.id){
			cout<<"modelo ya agregado"<<autoAgregar.id<<" ya existe"<<endl;
			return;
		}
	}
	listaVehiculos.push_back(autoAgregar);
	cout<<"Modelo agregadodo con existo"<<autoAgregar.id<<endl;
}

