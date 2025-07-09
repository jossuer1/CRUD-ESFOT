#include <iostream>
#include <fstream>
using namespace std;

void mostrar() {
    ifstream archivo("datos.txt"); // Abrimos el archivo para leer
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    // Luego leeremos el contenido
    archivo.close();
}
