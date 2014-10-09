#include "texturenode.h"

TextureNode::TextureNode(QQuickWindow *window)
    : m_id(0), m_size(0, 0)
    , m_texture(0), m_window(window)
{
    // Our texture node must have a texture, so use the default 0 texture.
    m_texture = m_window->createTextureFromId(0, QSize(1, 1));
    setTexture(m_texture);
    setFiltering(QSGTexture::Linear);
}

TextureNode::~TextureNode()
{
    delete m_texture;
}


// This function gets called on the FBO rendering thread and will store the
// texture id and size and schedule an update on the window.
void TextureNode::newTexture(int id, const QSize &size) {
    m_mutex.lock();
    m_id = id;
    m_size = size;
    m_mutex.unlock();

    // We cannot call QQuickWindow::update directly here, as this is only allowed
    // from the rendering thread or GUI thread.
    emit pendingNewTexture();
}


// Before the scene graph starts to render, we update to the pending texture
void TextureNode::prepareNode() {
    m_mutex.lock();
    int newId = m_id;
    QSize size = m_size;
    m_id = 0;
    m_mutex.unlock();
    if (newId) {
        delete m_texture;
        m_texture = m_window->createTextureFromId(newId, size);
        setTexture(m_texture);

        // This will notify the rendering thread that the texture is now being rendered
        // and it can start rendering to the other one.
        emit textureInUse();
    }
}
