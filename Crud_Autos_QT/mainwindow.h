#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void cargar_imagen();

private slots:

    void on_pushButtonAgregar_clicked();

    void on_TableVehiculos_cellClicked(int row, int column);

    void on_pushButtonLista_clicked();

    void on_pushButtonActualizar_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
