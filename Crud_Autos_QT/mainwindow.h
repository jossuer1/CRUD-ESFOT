#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>

using namespace std;

struct vehiculos {
    int id;
    string marca;
    string modelo;
    int año;
    double precio;
    int cantidad;
};

inline vector<vehiculos> listaVehiculos;
inline int contadorID = 1;

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

private slots:

    void on_pushButtonAgregar_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
