#ifndef NODECOORDS_H
#define NODECOORDS_H

#include <QtGlobal>
#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QDebug>

class NodeCoords
{
public:
    NodeCoords();

    QVector<QVector3D> getCoords();
    void setCoords(const QVector<QVector3D> &coords);

    QVector3D point1() const;
    void setPoint1(const QVector3D &point1);

    QVector3D point2() const;
    void setPoint2(const QVector3D &point2);

    QVector3D point3() const;
    void setPoint3(const QVector3D &point3);

    QVector3D point4() const;
    void setPoint4(const QVector3D &point4);

    void calcAllPoints(qreal width, qreal height);

private:

    QVector3D m_point1;
    QVector3D m_point2;
    QVector3D m_point3;
    QVector3D m_point4;
};

#endif // NODECOORDS_H
