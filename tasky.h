#ifndef TASKY_H
#define TASKY_H

#include <QMainWindow>
#include <QDebug>
#include <tarea.h>
#include <QMessageBox>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class Tasky; }
QT_END_NAMESPACE

class Tasky : public QMainWindow
{
    Q_OBJECT

public:
    Tasky(QWidget *parent = nullptr);
    ~Tasky();

private slots:
    void on_bpnagregar_clicked();
    void on_btnEliminar_clicked();

private:
    Ui::Tasky *ui;
    QList <Tarea*> m_tareas;
    const QString ARCHIVO="tarea.csv";
    /*archivos CSV
    -Archivod de texto
    -Para guar datos por campos
    -Cada linea es un resgistro
    -Cada dato se separa por comas,*/

    enum Columna{
        TAREA, ASIGNATURA, FECHA, HORA
    };
    void agregaratarea(Tarea *t);
    void limpiar();
    void guardar();
    void cargar();
    void actualizarColoresTabla();

};
#endif // TASKY_H
