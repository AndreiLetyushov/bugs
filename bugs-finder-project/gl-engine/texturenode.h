#ifndef TEXTURENODE_H
#define TEXTURENODE_H

#include <QObject>
#include <QSGSimpleTextureNode>
#include <QtQuick/QQuickWindow>

#include <QtCore/QMutex>


class TextureNode : public QObject, public QSGSimpleTextureNode
{
    Q_OBJECT
public:
    explicit TextureNode(QQuickWindow *window);
    ~TextureNode();

signals:
    void textureInUse();
    void pendingNewTexture();

public slots:
    void newTexture(int id, const QSize &size);
    void prepareNode();

private:

    int m_id;
    QSize m_size;

    QMutex m_mutex;

    QSGTexture *m_texture;
    QQuickWindow *m_window;

};

#endif // TEXTURENODE_H
