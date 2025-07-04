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

vector<vehiculos>listaVehiculos;

vector<vehiculos> leer(){
	return listaVehiculos;
};

int contadorID = 1;

void agregar(){
	vehiculos nuevo;
	nuevo.id = contadorID++;

	cout<<"Marca: ";
	getline(cin, nuevo.marca);
	cout<<"Modelo: ";
	getline(cin, nuevo.modelo);

	while (true){
		cout<<"Año: ";
		cin>>nuevo.año;
		if(nuevo.año >= 1950 && nuevo.año <=2025){
			break;
		}else{
			cout<<"Año ingresado invalido (SOLO AUTOS ENTRE 1980 Y 2025)"<<endl;
		}
	}

	cout<<"Precio: ";
	cin>>nuevo.precio;
	cin.ignore();

	for(auto& v : listaVehiculos){
		if(v.marca == nuevo.marca && v.modelo ==nuevo.modelo ){
			v.cantidad += 1;
			cout<<"Auto ya existente. Se añade a catalogo cone ID :"<<nuevo.id<<endl;
			return;
		}
	}

	nuevo.cantidad = 1;
	listaVehiculos.push_back(nuevo);
	cout<<"Nuevo modelo agregado con exito :3\n El ID generado es: "<<nuevo.id<<endl;
}

