#include "vehiculos.h"

bool agregarVehiculo(const string& marca,const string& modelo,int año,double precio){
	for(auto& v: listaVehiculos){
		if(v.marca== marca && v.modelo ==modelo){
			v.cantidad +=1;
			return true;
		}
	}
	Vehiculo nuevo;
	nuevo.id = contadorID++;
	nuevo.marca = marca;
	nuevo.modelo = modelo;
	nuevo.anio = año;
	nuevo.precio = precio;
	nuevo.cantidad = 1;

	listaVehiculos.push_back(nuevo);
	return false;

}


