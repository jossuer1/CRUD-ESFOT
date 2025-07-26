#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Estructura Vehiculo sin 'cantidad'
struct Vehiculo {
    int id;
    string marca;
    string modelo;
    int año;
    double precio;
};

// Variables globales
vector<Vehiculo> listaVehiculos;
int contadorID = 1;

// Convertir id a string "CAR_x"
string idToString(int id) {
    return "CAR_" + to_string(id);
}

// Convertir string "CAR_x" a int
int stringToId(const string& str) {
    if (str.find("CAR_") == 0) {
        try {
            return stoi(str.substr(4));
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Guardar vehículos en archivo
void guardarArchivo() {
    ofstream archivo("vehiculos.txt", ios::out);
    if (!archivo.is_open()) {
        qDebug() << "No se pudo abrir el archivo para guardar.";
        return;
    }
    for (const auto& v : listaVehiculos) {
        archivo << idToString(v.id) << "|"
                << v.marca << "|"
                << v.modelo << "|"
                << v.año << "|"
                << v.precio << "\n";
    }
    archivo.close();
}

// Cargar vehículos desde archivo
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
        string idStr, marcaStr, modeloStr, añoStr, precioStr;

        if (!getline(ss, idStr, '|')) continue;
        if (!getline(ss, marcaStr, '|')) continue;
        if (!getline(ss, modeloStr, '|')) continue;
        if (!getline(ss, añoStr, '|')) continue;
        if (!getline(ss, precioStr, '|')) continue;

        Vehiculo v;
        try {
            v.id = stringToId(idStr);
            v.marca = marcaStr;
            v.modelo = modeloStr;
            v.año = stoi(añoStr);
            v.precio = stod(precioStr);
        } catch (...) {
            continue;
        }

        listaVehiculos.push_back(v);
        if (v.id > maxID) maxID = v.id;
    }

    contadorID = maxID + 1;
    archivo.close();
}

// Agregar nuevo vehículo
void agregarVehiculo(const string& marca, const string& modelo, int año, double precio) {
    Vehiculo nuevo;
    nuevo.id = contadorID++;
    nuevo.marca = marca;
    nuevo.modelo = modelo;
    nuevo.año = año;
    nuevo.precio = precio;

    listaVehiculos.push_back(nuevo);
}

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cargarDesdeArchivo();
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

    agregarVehiculo(marca, modelo, año, precio);
    guardarArchivo();
    on_pushButtonLista_clicked();

    ui->lineEditMarca->clear();
    ui->lineEditModelo->clear();
    ui->spinBoxAnio->setValue(2000);
    ui->lineEditPrecio->clear();

    QMessageBox::information(this, "Vehículo guardado", "Vehículo agregado exitosamente.");
}

int idSeleccionado = -1;

// Al hacer click en un vehículo de la tabla
void MainWindow::on_TableVehiculos_cellClicked(int row, int)
{
    auto* itemID = ui->TableVehiculos->item(row, 0);
    if(itemID)
        idSeleccionado = stringToId(itemID->text().toStdString());

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
    ui->TableVehiculos->setColumnCount(5); // ID, Marca, Modelo, Año, Precio

    for (int i = 0; i < listaVehiculos.size(); ++i) {
        const auto& v = listaVehiculos[i];
        ui->TableVehiculos->insertRow(i);
        ui->TableVehiculos->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(idToString(v.id))));
        ui->TableVehiculos->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(v.marca)));
        ui->TableVehiculos->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(v.modelo)));
        ui->TableVehiculos->setItem(i, 3, new QTableWidgetItem(QString::number(v.año)));
        ui->TableVehiculos->setItem(i, 4, new QTableWidgetItem(QString::number(v.precio, 'f', 2)));
    }
}

//boton Actualizar

void MainWindow::on_pushButtonActualizar_clicked()
{
    if (idSeleccionado == -1) {
        QMessageBox::warning(this, "Selección requerida", "Selecciona un vehículo de la tabla para actualizar.");
        return;
    }

    QString marcaQt = ui->lineEditMarca->text();
    QString modeloQt = ui->lineEditModelo->text();
    int año = ui->spinBoxAnio->value();
    QString precioQt = ui->lineEditPrecio->text();

    if (marcaQt.isEmpty() || modeloQt.isEmpty() || precioQt.isEmpty()) {
        QMessageBox::warning(this, "Campos vacíos", "Por favor, llena todos los campos.");
        return;
    }

    string marca = marcaQt.toStdString();
    string modelo = modeloQt.toStdString();
    double precio = precioQt.toDouble();

    // Buscar y actualizar
    for (auto& v : listaVehiculos) {
        if (v.id == idSeleccionado) {
            v.marca = marca;
            v.modelo = modelo;
            v.año = año;
            v.precio = precio;

            break;
        }
    }

    guardarArchivo();
    QMessageBox::information(this, "Actualizado", "Vehículo actualizado correctamente.");
    on_pushButtonLista_clicked(); // refrescar tabla
}

