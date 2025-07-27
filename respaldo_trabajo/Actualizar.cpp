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

