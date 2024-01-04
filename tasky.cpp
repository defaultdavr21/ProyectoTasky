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
    cargar();
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
    actualizarColoresTabla();
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
void Tasky::cargar(){

    QFile archivo(ARCHIVO);
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream entrada(&archivo);

        while (!entrada.atEnd())
        {
            QString linea = entrada.readLine();
            QStringList datos = linea.split(";");
            QString nombre = datos[0];
            QString asignatura = datos[1];
            QStringList fecha = datos[2].split("/");
            QDate f(fecha[2].toInt(), fecha[1].toInt(), fecha[0].toInt());
            QStringList hora = datos[3].split(":");
            QTime h(hora[0].toInt(), hora[1].toInt());

            //QDate fecha = QDate::fromString(datos[2], "dd/MM/yyyy");
            //QTime hora = QTime::fromString(datos[3], "hh:mm");

            Tarea *t = new Tarea( asignatura, f, h,nombre);
            agregaratarea(t);
        }

        archivo.close();
    }
    else
    {
        QMessageBox::critical(this, "Cargar tareas", "No se puede leer desde " + ARCHIVO);
    }
}


void Tasky::actualizarColoresTabla() {
    QDate hoy = QDate::currentDate();

    for (int fila = 0; fila < ui->tbltareas->rowCount(); ++fila) {
        QDate fechaTarea = QDate::fromString(ui->tbltareas->item(fila, FECHA)->text(), "dd/MM/yyyy");

        // Calcular la diferencia en días
        int diasRestantes = hoy.daysTo(fechaTarea);

        // Establecer el color de fondo en función de la diferencia en días
        if (diasRestantes > 1) {
            ui->tbltareas->item(fila, TAREA)->setBackground(QBrush(QColor(Qt::green)));
            ui->tbltareas->item(fila, ASIGNATURA)->setBackground(QBrush(QColor(Qt::green)));
            ui->tbltareas->item(fila, FECHA)->setBackground(QBrush(QColor(Qt::green)));
            ui->tbltareas->item(fila, HORA)->setBackground(QBrush(QColor(Qt::green)));
        } else if (diasRestantes == 1 ) {
            ui->tbltareas->item(fila, TAREA)->setBackground(QBrush(QColor(Qt::red)));
            ui->tbltareas->item(fila, ASIGNATURA)->setBackground(QBrush(QColor(Qt::red)));
            ui->tbltareas->item(fila, FECHA)->setBackground(QBrush(QColor(Qt::red)));
            ui->tbltareas->item(fila, HORA)->setBackground(QBrush(QColor(Qt::red)));
        } else if (diasRestantes == 0) {

            ui->tbltareas->item(fila, TAREA)->setBackground(QBrush(QColor(Qt::red)));
            ui->tbltareas->item(fila, ASIGNATURA)->setBackground(QBrush(QColor(Qt::red)));
            ui->tbltareas->item(fila, FECHA)->setBackground(QBrush(QColor(Qt::red)));
            ui->tbltareas->item(fila, HORA)->setBackground(QBrush(QColor(Qt::red)));
        } else {
            // Si no cumple ninguna condición, se puede restaurar el color predeterminado
            ui->tbltareas->item(fila, TAREA)->setBackground(QBrush());
            ui->tbltareas->item(fila, ASIGNATURA)->setBackground(QBrush());
            ui->tbltareas->item(fila, FECHA)->setBackground(QBrush());
            ui->tbltareas->item(fila, HORA)->setBackground(QBrush());
        }
    }
}

void Tasky::on_btnEliminar_clicked(){

    int filaSeleccionada = ui->tbltareas->currentRow();

    // Verificar si se seleccionó una fila válida
    if (filaSeleccionada >= 0 && filaSeleccionada < ui->tbltareas->rowCount()) {
        // Eliminar la tarea de la lista y de la tabla
        Tarea *t = m_tareas.takeAt(filaSeleccionada);
        delete t;

        ui->tbltareas->removeRow(filaSeleccionada);
        guardar();
    } else {
        QMessageBox::warning(this, "Eliminar tarea", "Selecciona una tarea para eliminar.");
    }
}


