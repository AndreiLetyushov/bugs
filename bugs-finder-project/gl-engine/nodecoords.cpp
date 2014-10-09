#include "nodecoords.h"

NodeCoords::NodeCoords()
{
}


QVector<QVector3D> NodeCoords::getCoords()
{
    QVector<QVector3D> points;
    points << m_point1;
    points << m_point2;
    points << m_point3;
    points << m_point4;
    return points;
}

void NodeCoords::setCoords(const QVector<QVector3D> &coords)
{
    m_point1 = coords.at(0);
    m_point2 = coords.at(1);
    m_point3 = coords.at(2);
    m_point4 = coords.at(3);
}

QVector3D NodeCoords::point1() const
{
    return m_point1;
}

void NodeCoords::setPoint1(const QVector3D &point1)
{
    m_point1 = point1;
}
QVector3D NodeCoords::point2() const
{
    return m_point2;
}

void NodeCoords::setPoint2(const QVector3D &point2)
{
    m_point2 = point2;
}
QVector3D NodeCoords::point3() const
{
    return m_point3;
}

void NodeCoords::setPoint3(const QVector3D &point3)
{
    m_point3 = point3;
}
QVector3D NodeCoords::point4() const
{
    return m_point4;
}

void NodeCoords::setPoint4(const QVector3D &point4)
{
    m_point4 = point4;
}

void NodeCoords::calcAllPoints(qreal width, qreal height)
{
    m_point2 = QVector3D(m_point1.x(), m_point1.y() + height, m_point1.z());
    m_point3 = QVector3D(m_point1.x() + width, m_point1.y() + height, m_point1.z());
    m_point4 = QVector3D(m_point1.x() + width, m_point1.y(), m_point1.z());
}
