/*
 * The render thread shares a context with the scene graph and will
 * render into two separate FBOs, one to use for display and one
 * to use for rendering
 */

#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include "screennode.h"

#include <QThread>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QOpenGLContext>
#include <QtGui/QGuiApplication>

class RenderThread : public QThread
{
    Q_OBJECT
public:
    explicit RenderThread(const QSize &size, QObject *parent = 0);

    QOffscreenSurface *surface;
    QOpenGLContext *context;

signals:
    void textureReady(int id, const QSize &size);

public slots:
    void renderNext();
    void shutDown();

private:
    QOpenGLFramebufferObject *m_renderFbo;
    QOpenGLFramebufferObject *m_displayFbo;

    QSize m_size;

    QSharedPointer<MainScene> m_scene;

    void buildSceneTree(int textureNumber);
    void initialize();
    void render();

    qint32 m_counter;

    QMap <QString, QOpenGLTexture *> m_textures;
};

#endif // RENDERTHREAD_H
