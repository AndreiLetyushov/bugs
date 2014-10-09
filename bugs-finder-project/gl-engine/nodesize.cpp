#include "nodesize.h"

NodeSize::NodeSize(qreal width, qreal height)
    : m_width(width), m_height(height)
{

}
qreal NodeSize::width() const
{
    return m_width;
}

void NodeSize::setWidth(const qreal &width)
{
    m_width = width;
}
qreal NodeSize::height() const
{
    return m_height;
}

void NodeSize::setHeight(const qreal &height)
{
    m_height = height;
}







