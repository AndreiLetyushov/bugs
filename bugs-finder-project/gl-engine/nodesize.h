#ifndef NODESIZE_H
#define NODESIZE_H

#include <QtGlobal>

class NodeSize
{
public:
    NodeSize(qreal width = 0.0, qreal height = 0.0);

    qreal width() const;
    void setWidth(const qreal &width);

    qreal height() const;
    void setHeight(const qreal &height);

private:
    qreal m_width;
    qreal m_height;

};

#endif // NODESIZE_H
