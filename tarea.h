#ifndef TAREA_H
#define TAREA_H
#include <QObject>
#include <QDate>

class Tarea : public QObject
{
    Q_OBJECT
private:
    QString m_asignatura;
    QDate m_fecha;
    QTime m_hora;
    QString m_nombre;

public:
    explicit Tarea(QObject *parent = nullptr);
    Tarea(const QString &asignatura, const QDate &fecha, const QTime &hora, const QString &nombre);
    const QString &asignatura() const;

    void setAsignatura(const QString &newAsignatura);
    const QDate &fecha() const;
    void setFecha(const QDate &newFecha);
    const QTime &hora() const;
    void setHora(const QTime &newHora);
    const QString &nombre() const;
    void setNombre(const QString &newNombre);

signals:

};

#endif // TAREA_H
