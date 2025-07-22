#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <vector>
#include <string>
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

//FUNCIONES
bool agregarVehiculo(const string& marca,const string& modelo,int año,double precio);


//Agregar vehiculo

bool agregarVehiculo(const string& marca,const string& modelo,int año,double precio){
    for(auto& v: listaVehiculos){
        if(v.marca== marca && v.modelo ==modelo && v.precio == precio){
            v.cantidad +=1;
             //guardarEnArchivo();
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
    //guardarEnArchivo();
    return false;
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cargar_imagen();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargar_imagen()
{
    // Imagen del carro
    QPixmap imagenCarro("Picture/39726-banedikt.jpg");
    if (!imagenCarro.isNull()) {
        ui->label_Carro->setPixmap(imagenCarro);
    } else {
        qDebug() << "No se pudo cargar la imagen del carro.";
    }

    // Imagen del logo
    QPixmap logo("Picture/logo_esfot_buho.png");
    if (!logo.isNull()) {
        ui->label_Esfot->setPixmap(logo);
    } else {
        qDebug() << "No se pudo cargar el logo.";
    }
    //Imagen de logo EPN
    QPixmap logo_EPN("Picture/logo-epn-vertical.png");
    if (!logo.isNull()) {
        ui->label_EPN->setPixmap(logo_EPN);
    } else {
        qDebug() << "No se pudo cargar el logo.";
    }
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

    ui->lineEditMarca->clear();
    ui->lineEditModelo->clear();
    ui->spinBoxAnio->setValue(2000);
    ui->lineEditPrecio->clear();

    QMessageBox::information(this, "Vehículo guardado", repetido ?
            "Cantidad aumentada en 1." : "Vehículo nuevo agregado con cantidad 1.");
}


