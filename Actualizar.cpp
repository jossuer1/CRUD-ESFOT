#include "vehiculos.h"
using namespace std;

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

		if(!guardarVehiculo(listaVehiculos,"autos.txt")){
			return false;
		}
		return true;
			
	   }
	}
        return false;
}






