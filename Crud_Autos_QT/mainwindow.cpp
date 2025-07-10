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
        QMessageBox::warning(this, "Campos vacíos", "Por favor, llena todos los campos");
        return;
    }

    string marca = marcaQt.toStdString();
    string modelo = modeloQt.toStdString();
    double precio = precioQt.toDouble();

    bool repetido = agregarVehiculo(marca, modelo, año, precio);

    ui->lineEditMarca->clear();
    ui->lineEditModelo->clear();
    ui->spinBoxAnio->setValue(2000);
    ui->lineEditPrecio->clear();

    QMessageBox::information(this, "Vehículo guardado", repetido ?
            "Cantidad aumentada en 1." : "Vehículo nuevo agregado con cantidad 1.");
}


