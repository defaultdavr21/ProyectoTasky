#include "tasky.h"
#include "ui_tasky.h"

Tasky::Tasky(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasky)
{
    ui->setupUi(this);//todo lo que hago aqui se crea en la interfaz grafica
    QDate hoy = QDate::currentDate();// Toma la fecha de la maquina donde trabajo
    QTime ahora = QTime::currentTime();// Toma la hora de la maquina
    ui->datfecha->setMinimumDate(hoy);
    ui->datfecha->setDate(hoy);
    ui->dthora->setTime(ahora);

    ui->tbltareas->setColumnCount(4);
    QStringList cabecera;
    cabecera << "Tarea"<< "Asignatura"<< "Fecha"<< "Hora";
    ui->tbltareas->setHorizontalHeaderLabels(cabecera);
}

Tasky::~Tasky()
{
    delete ui;
}


void Tasky::on_bpnagregar_clicked(){

    QString nombre= ui->txtTarea->text();
    QString asignatura= ui->cmbasignatura->currentText();
    QDate fecha = ui->datfecha->date();
    QTime hora = ui->dthora->time();

    /*Tarea t(asignatura,fecha,hora,nombre);
    qDebug()<<t.nombre();*/

    //creo una tarea
    //Tarea t(asignatura,fecha,hora,nombre);
    // agrego la tarea a la lista
    m_tareas.append(new Tarea(asignatura,fecha,hora,nombre));





}

