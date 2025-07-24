#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Estructura Vehiculo con id entero
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

// Función auxiliar para convertir id entero a formato "CAR_x"
string idToString(int id) {
    return "CAR_" + to_string(id);
}

// Función auxiliar para extraer número desde string "CAR_x"
int stringToId(const string& str) {
    if (str.find("CAR_") == 0) {
        try {
            return stoi(str.substr(4));
        } catch (...) {
            return 0; // En caso de error
        }
    }
    return 0; // Si no tiene formato esperado
}

// Guardar listaVehiculos en archivo "vehiculos.txt" con formato "CAR_x"
void guardarArchivo() {
    ofstream archivo("vehiculos.txt", ios::out);
    if (!archivo.is_open()) {
        qDebug() << "No se pudo abrir el archivo para guardar.";
        return;
    }
    for (const auto& v : listaVehiculos) {
        archivo << idToString(v.id) << "|"  // Guardamos con formato "CAR_x"
                << v.marca << "|"
                << v.modelo << "|"
                << v.año << "|"
                << v.precio << "|"
                << v.cantidad << "\n";
    }
    archivo.close();
}

// Cargar listaVehiculos desde archivo "vehiculos.txt" leyendo id con formato "CAR_x"
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
            v.id = stringToId(idStr);  // Convertimos "CAR_x" a int
            v.marca = marcaStr;
            v.modelo = modeloStr;
            v.año = stoi(añoStr);
            v.precio = stod(precioStr);
            v.cantidad = stoi(cantidadStr);
        } catch (...) {
            continue;
        }

        listaVehiculos.push_back(v);

        if (v.id > maxID) {
            maxID = v.id;
        }
    }

    contadorID = maxID + 1;
    archivo.close();
}

// Agregar vehículo
bool agregarVehiculo(const string& marca, const string& modelo, int año, double precio) {
    for (auto& v : listaVehiculos) {
        if (v.marca == marca && v.modelo == modelo && v.precio == precio) {
            v.cantidad += 1;
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

// Botón Agregar
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

    on_pushButtonLista_clicked(); // Actualizar tabla con nuevo vehículo

    ui->lineEditMarca->clear();
    ui->lineEditModelo->clear();
    ui->spinBoxAnio->setValue(2000);
    ui->lineEditPrecio->clear();

    QMessageBox::information(this, "Vehículo guardado", repetido ?
                                                            "Cantidad aumentada en 1." : "Vehículo nuevo agregado con cantidad 1.");
}

int idSeleccionado = -1;

// Cuando se hace click en una celda de la tabla para seleccionar vehículo
void MainWindow::on_TableVehiculos_cellClicked(int row, int ver)
{
    auto* itemID = ui->TableVehiculos->item(row, 0);
    if(itemID)
        idSeleccionado = stringToId(itemID->text().toStdString()); // Convertir "CAR_x" a int

    auto* itemMarca = ui->TableVehiculos->item(row, 1);
    auto* itemModelo = ui->TableVehiculos->item(row, 2);
    auto* itemAnio = ui->TableVehiculos->item(row, 3);
    auto* itemPrecio = ui->TableVehiculos->item(row, 4);

    if(itemMarca) ui->lineEditMarca->setText(itemMarca->text());
    if(itemModelo) ui->lineEditModelo->setText(itemModelo->text());
    if(itemAnio) ui->spinBoxAnio->setValue(itemAnio->text().toInt());
    if(itemPrecio) ui->lineEditPrecio->setText(itemPrecio->text());
}

// Botón Listar
void MainWindow::on_pushButtonLista_clicked()
{
    ui->TableVehiculos->clearContents();
    ui->TableVehiculos->setRowCount(0);

    for (int i = 0; i < listaVehiculos.size(); ++i) {
        const auto& v = listaVehiculos[i];
        ui->TableVehiculos->insertRow(i);
        ui->TableVehiculos->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(idToString(v.id))));  // Mostrar como "CAR_x"
        ui->TableVehiculos->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(v.marca)));
        ui->TableVehiculos->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(v.modelo)));
        ui->TableVehiculos->setItem(i, 3, new QTableWidgetItem(QString::number(v.año)));
        ui->TableVehiculos->setItem(i, 4, new QTableWidgetItem(QString::number(v.precio, 'f', 2)));
        ui->TableVehiculos->setItem(i, 5, new QTableWidgetItem(QString::number(v.cantidad)));
    }
}
