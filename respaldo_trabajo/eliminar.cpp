
//boton eliminar
void MainWindow::on_pushButtonEliminar_clicked()
{
    if (idSeleccionado == -1) {
        QMessageBox::warning(this, "Selección requerida", "Selecciona un vehículo de la tabla para eliminar.");
        return;
    }

    auto respuesta = QMessageBox::question(this, "Confirmar eliminación",
                                           "¿Estás seguro de que deseas eliminar este vehículo?",
                                           QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::No)
        return;

    // Eliminar del vector
    auto it = std::remove_if(listaVehiculos.begin(), listaVehiculos.end(),
                             [](const Vehiculo& v) {
                                 return v.id == idSeleccionado;
                             });

    if (it != listaVehiculos.end()) {
        listaVehiculos.erase(it, listaVehiculos.end());
        guardarArchivo();
        QMessageBox::information(this, "Eliminado", "Vehículo eliminado correctamente.");
        on_pushButtonLista_clicked(); // Refrescar tabla
    } else {
        QMessageBox::warning(this, "Error", "No se pudo eliminar el vehículo.");
    }

    // Limpiar selección y campos
    idSeleccionado = -1;
    ui->lineEditMarca->clear();
    ui->lineEditModelo->clear();
    ui->spinBoxAnio->setValue(2000);
    ui->lineEditPrecio->clear();
}

