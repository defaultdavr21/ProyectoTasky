#include "tasky.h"
#include "ui_tasky.h"

Tasky::Tasky(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasky){

    ui->setupUi(this);//todo lo que hago aqui se crea en la interfaz grafica
    limpiar();
    ui->tbltareas->setColumnCount(4);
    QStringList cabecera;
    cabecera << "Tarea"<< "Asignatura"<< "Fecha"<< "Hora";
    ui->tbltareas->setHorizontalHeaderLabels(cabecera);
}

Tasky::~Tasky(){
    delete ui;
}

void Tasky::on_bpnagregar_clicked(){

    QString nombre= ui->txtTarea->text();
    //validar que e nombre de la tarea no este vacio
    if(nombre.length()==0){
        QMessageBox::warning(this,"Agregar tarea","El nombre de la tarea no puede estar vacio");
        return;
    }
    QString asignatura= ui->cmbasignatura->currentText();
    QDate fecha = ui->datfecha->date();
    QTime hora = ui->dthora->time();
    //Creo una tarea
    Tarea *t=new Tarea(asignatura,fecha,hora,nombre);
    //agregar la tarea
    agregaratarea(t);
    limpiar();
    guardar();

}

void Tasky::agregaratarea(Tarea *t){

    //agrego a la lista
    m_tareas.append(t);
    int fila = ui->tbltareas->rowCount();
    ui->tbltareas->insertRow(fila);
    ui->tbltareas->setItem(fila, TAREA, new QTableWidgetItem(t->nombre()));
    ui->tbltareas->setItem(fila, ASIGNATURA, new QTableWidgetItem(t->asignatura()));
    ui->tbltareas->setItem(fila, FECHA, new QTableWidgetItem(t->fecha().toString("dd/MM/yyyy")));
    ui->tbltareas->setItem(fila, HORA, new QTableWidgetItem(t->hora().toString("hh:mm")));

}

void Tasky::limpiar(){

    QDate hoy = QDate::currentDate();// Toma la fecha de la maquina donde trabajo
    QTime ahora = QTime::currentTime();// Toma la hora de la maquina
    ui->datfecha->setMinimumDate(hoy);
    ui->datfecha->setDate(hoy);
    ui->dthora->setTime(ahora);
    //limpiar campos
    ui->txtTarea->clear();
    ui->cmbasignatura->setCurrentIndex(0);
    //Setea el foco al campo de tarea
    ui->txtTarea->setFocus();

}

void Tasky::guardar(){



    // Abrir el archivo y guardar
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream salida(&archivo);
        Tarea *t;
        foreach(t,  m_tareas){
            salida<<t->nombre()<<";"<<t->asignatura()<<";";
            salida<<t->fecha().toString("dd/MM/yyyy")<<";";
            salida<<t->hora().toString("hh:mm")<<"\n";

        }
        archivo.close();
        //QMessageBox::information(this,"Guardar contactos","Contactos guardados con éxito");
    }else{
        QMessageBox::critical(this,"Guardar tareas", "No se puede escribir sobre " + ARCHIVO);
    }
    /*
    1. Cuando se abra la aplicacion tego que leer el archivo
    2. con el split separo campos
    3. Instancio una tarea
    4. agregarTarea(*t)

    */
}





