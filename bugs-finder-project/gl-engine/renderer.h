#ifndef RENDERER_H
#define RENDERER_H

#include "renderthread.h"

#include <QQuickItem>

class Renderer : public QQuickItem
{
    Q_OBJECT

public:
    Renderer();

    static QList<QThread *> threads;

public Q_SLOTS:

    void ready();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

private:
    RenderThread *m_renderThread;
};

#endif
