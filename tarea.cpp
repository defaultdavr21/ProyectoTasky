#include "tarea.h"

Tarea::Tarea(QObject *parent)
    : QObject{parent} {

}
void Tarea::setAsignatura(const QString &newAsignatura){
    m_asignatura = newAsignatura;
}

const QDate &Tarea::fecha() const{
    return m_fecha;
}

void Tarea::setFecha(const QDate &newFecha){
    m_fecha = newFecha;
}

const QTime &Tarea::hora() const{
    return m_hora;
}

void Tarea::setHora(const QTime &newHora){
    m_hora = newHora;
}

const QString &Tarea::nombre() const{
    return m_nombre;
}

void Tarea::setNombre(const QString &newNombre){
    m_nombre = newNombre;
}

Tarea::Tarea(const QString &asignatura, const QDate &fecha, const QTime &hora, const QString &nombre) : m_asignatura(asignatura),
    m_fecha(fecha),
    m_hora(hora),
    m_nombre(nombre){

}
