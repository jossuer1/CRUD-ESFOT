#include "vehiculos.h"
#include <fstream>
#include <string>
#include <sstream>

bool guardarVehiculos(const vector<Vehiculo>& lista, const string& archivo){
	ofstream file(arhivo);
	if(!file.is_open()){
	    return false;
	}
	for(const Vehiculo& v:lista){
	    file << v.id<<","<< v.marca<<","<< v.modelo<<","
		 << v.anio<<","<< v.precio<<","<< v.cantidad <<"\n";  
	}
	file.close();
	return true;
}
	       
bool actualizarVehiculo (int id, const QString& nuevaMarca, const QString& nuevoModelo , int nuevoAnio, float nuevoPrecio){
	for(auto& v:listaVehiculos) {
           if (v.id == id){
               if(nuevoAnio < 1950 || nuevoAnio  > 2025){
                return false;
	       }
               v.marca = nuevaMarca;
               v.modelo = nuevoModelo;
               v.anio = nuevoAnio;
               v.precio = nuevoPrecio;

	       return guardarVehiculos(listaVehiculos,"autos.txt") ;  	
	   }
	}
        return false;
}








