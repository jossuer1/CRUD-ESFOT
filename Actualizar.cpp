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
	bool encontrado = false;
	
	for(auto &  v:listaVehiculos){
		if(v.id == idAuto){
			encontrado = true;
			cout<<"Vehiculo encontrado"<<endl;
			cout<<"Datos Actuales: "<<endl;
			cout<<"Marca: "<<v.marca<<endl;
			cout<<"Modelo: "<<v.modelo<<endl;
			cout<<"Anio: "<<v.año<<endl;
			cout<<"Precio: $"<<v.precio<<endl;
			cout<<"Cantidad: "<<v.cantidad<<endl;

			string opcion;
			cout<<"¿Desea modificar la marca? (Escriba Si para confirmar): ";
			getline(cin,opcion);
			if (opcion == "Si"){
				cout<<"Nueva Marca: ";
				getline(cin,v.marca);
			}
			cout<<"¿Desea modificar el modelo? (Escriba Si para confirmar): ";
			getline(cin,opcion);
			if (opcion == "Si"){
				cout<<"Nuevo modelo: ";
				getline(cin,v.modelo);
			}
			while (true){
				cout<<"¿Desea modificar el anio? (Escriba Si para confirmar): ";
				getline(cin,opcion);
				if (opcion == "Si"){
					cout<<"Nuevo anio: ";
					cin>>v.año;
					cin.ignore();
					if(v.año >= 1950 && v.año <= 2025){
						break;
					}else {
					cout<<"Anio ingresado invalido (Solo autos entre 1995 y 2025) " <<endl;
				}else{
					break;
				}
			}

			cout<<"¿Desea modificar el precio? (Escriba Si para confirmar): ";
			getline(cin,opcion);
			if (opcion == "Si"){
				cout<<"Nuevo precio: ";
				cin>>v.precio;
				cin.ignore();
			}
			
			cout<<"Datos actualizados correctamente.\n";
			return;
		}
	}
	if (!encontrado){
		cout<<"No se encontro un vehiculo con ese ID.\n";
	}
}




