#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Estructura Vehiculo
struct Vehiculo {
    int id;
    string marca;
    string modelo;
    int año;
    double precio;
    int cantidad;
};

// Variables globales
vector<Vehiculo> listaVehiculos;
int contadorID = 1;

// FUNCIONES
bool agregarVehiculo(const string& marca,const string& modelo,int año,double precio);

// Guardar listaVehiculos en archivo "vehiculos.txt"
void guardarArchivo() {
    ofstream archivo("vehiculos.txt", ios::out);
    if (!archivo.is_open()) {
        qDebug() << "No se pudo abrir el archivo para guardar.";
        return;
    }
    for (const auto& v : listaVehiculos) {
        archivo << v.id << "|"
                << v.marca << "|"
                << v.modelo << "|"
                << v.año << "|"
                << v.precio << "|"
                << v.cantidad << "\n";
    }
    archivo.close();
}

// Cargar listaVehiculos desde archivo "vehiculos.txt"
void cargarDesdeArchivo() {
    ifstream archivo("vehiculos.txt");
    if (!archivo.is_open()) {
        qDebug() << "No se pudo abrir el archivo para leer.";
        return;
    }

    string linea;
    int maxID = 0;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string idStr, marcaStr, modeloStr, añoStr, precioStr, cantidadStr;

        if (!getline(ss, idStr, '|')) continue;
        if (!getline(ss, marcaStr, '|')) continue;
        if (!getline(ss, modeloStr, '|')) continue;
        if (!getline(ss, añoStr, '|')) continue;
        if (!getline(ss, precioStr, '|')) continue;
        if (!getline(ss, cantidadStr, '|')) continue;

        Vehiculo v;
        try {
            v.id = stoi(idStr);
            v.marca = marcaStr;
            v.modelo = modeloStr;
            v.año = stoi(añoStr);
            v.precio = stod(precioStr);
            v.cantidad = stoi(cantidadStr);
        } catch (...) {
            continue;
        }

        listaVehiculos.push_back(v);

        if (v.id > maxID){
             maxID = v.id;
        }
    }

    contadorID = maxID + 1;
    archivo.close();
}

// Agregar vehiculo
bool agregarVehiculo(const string& marca,const string& modelo,int año,double precio){
    for(auto& v: listaVehiculos){
        if(v.marca == marca && v.modelo == modelo && v.precio == precio){
            v.cantidad +=1;
            return true;
        }
    }
    Vehiculo nuevo;
    nuevo.id = contadorID++;
    nuevo.marca = marca;
    nuevo.modelo = modelo;
    nuevo.año = año;
    nuevo.precio = precio;
    nuevo.cantidad = 1;

    listaVehiculos.push_back(nuevo);
    return false;
}

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cargarDesdeArchivo();  // Carga los datos guardados al iniciar
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// boton Agregar
void MainWindow::on_pushButtonAgregar_clicked()
{
    QString marcaQt = ui->lineEditMarca->text();
    QString modeloQt = ui->lineEditModelo->text();
    int año = ui->spinBoxAnio->value();
    QString precioQt = ui->lineEditPrecio->text();

    if (marcaQt.isEmpty() || modeloQt.isEmpty() || precioQt.isEmpty()) {
        QMessageBox::warning(this, "Campos vacíos", "Por favor, llena todos los campos");
        return;
    }

    string marca = marcaQt.toStdString();
    string modelo = modeloQt.toStdString();
    double precio = precioQt.toDouble();

    bool repetido = agregarVehiculo(marca, modelo, año, precio);

    guardarArchivo();

    ui->lineEditMarca->clear();
    ui->lineEditModelo->clear();
    ui->spinBoxAnio->setValue(2000);
    ui->lineEditPrecio->clear();

    QMessageBox::information(this, "Vehículo guardado", repetido ?
                                                            "Cantidad aumentada en 1." : "Vehículo nuevo agregado con cantidad 1.");
}

