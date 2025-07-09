#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "../vehiculos.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAgregar_clicked()
{
    QString marcaQt = ui->lineEditMarca->text();
    QString modeloQt = ui->lineEditModelo->text();
    int año = ui->spinBoxAnio->value();
    QString precioQt = ui->lineEditPrecio->text();

    if (marcaQt.isEmpty() || modeloQt.isEmpty() || precioQt.isEmpty()) {
        QMessageBox::warning(this, "Campos vacíos", "Por favor, llena todos los campos excepto 'cantidad'.");
        return;
    }

    string marca = marcaQt.toStdString();
    string modelo = modeloQt.toStdString();
    double precio = precioQt.toDouble();

    bool encontrado = false;
    for (auto &v : listaVehiculos) {
        if (v.marca == marca && v.modelo == modelo) {
            v.cantidad += 1;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        Vehiculo nuevo;
        nuevo.id = contadorID++;
        nuevo.marca = marca;
        nuevo.modelo = modelo;
        nuevo.año = año;
        nuevo.precio = precio;
        nuevo.cantidad = 1;
        listaVehiculos.push_back(nuevo);
    }

    ui->lineEditMarca->clear();
    ui->lineEditModelo->clear();
    ui->spinBoxAnio->setValue(2000);
    ui->lineEditPrecio->clear();

    QMessageBox::information(this, "Vehículo guardado", encontrado ?
    "Cantidad aumentada en 1." :"Vehículo nuevo agregado con cantidad 1.");
}

