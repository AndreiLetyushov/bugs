#include "renderthread.h"
#include "renderer.h"



RenderThread::RenderThread(const QSize &size, QObject *parent)
    : QThread(parent), surface(0), context(0), m_renderFbo(0), m_displayFbo(0), m_size(size)
{
    m_counter = 0;
    Renderer::threads << this;
}

void RenderThread::buildSceneTree(int textureNumber)
{
    m_scene->clear();

    QSharedPointer<FixedScreenNode> desk1 = QSharedPointer<FixedScreenNode>::create(m_scene);
    QSharedPointer<FixedScreenNode> desk2 = QSharedPointer<FixedScreenNode>::create(m_scene);
    QSharedPointer<FixedScreenNode> desk3 = QSharedPointer<FixedScreenNode>::create(m_scene);

    qDebug() << glGetError();
    desk1->setTexture(m_textures[QString::number(textureNumber)]);
    desk1->setStartPoint(0.0, 0.0, 0.0, ScreenNode::TypeOfCoords::RelativeScene);
    desk1->setSize(0.3, 1.0);
    qDebug() << glGetError();
    desk2->setTexture(m_textures[QString::number(textureNumber)]);
    desk2->setStartPoint(0.3, 0.0, 0.0, ScreenNode::TypeOfCoords::RelativeScene);
    desk2->setSize(0.7, 0.8);
    qDebug() << glGetError();
    desk3->setTexture(m_textures[QString::number(textureNumber)]);
    desk3->setStartPoint(0.3, 0.8, 0.0, ScreenNode::TypeOfCoords::RelativeScene);
    desk3->setSize(0.7, 0.2);
    qDebug() << glGetError();
    m_scene->addChild(desk1);
    m_scene->addChild(desk2);
    m_scene->addChild(desk3);
}

void RenderThread::renderNext()
{
    context->makeCurrent(surface);

    if (!m_renderFbo) {
        // Initialize the buffers and renderer
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        m_renderFbo = new QOpenGLFramebufferObject(m_size, format);
        m_displayFbo = new QOpenGLFramebufferObject(m_size, format);

        m_scene = QSharedPointer<MainScene>::create();

        m_textures["background"] = new QOpenGLTexture(QImage(":/images/blue.jpg"));

        for(int x = 0; x < 20; x++)
            m_textures[QString::number(x)] = new QOpenGLTexture(QImage(":/images/" + QString::number(x+1) + ".jpg"));


        m_scene->setTexture(m_textures["background"]);

        buildSceneTree(0);
    }


    if(++m_counter/30 < 18)
        buildSceneTree(m_counter / 30);
    else
        m_counter = 0;


    m_renderFbo->bind();
    glViewport(0, 0, m_size.width(), m_size.height());

    m_scene->render();
    // We need to flush the contents to the FBO before posting
    // the texture to the other thread, otherwise, we might
    // get unexpected results.
    glFlush();

    m_renderFbo->bindDefault();
    qSwap(m_renderFbo, m_displayFbo);

    emit textureReady(m_displayFbo->texture(), m_size);
}

void RenderThread::shutDown()
{
    context->makeCurrent(surface);
    delete m_renderFbo;
    delete m_displayFbo;
    context->doneCurrent();
    delete context;

    // schedule this to be deleted only after we're done cleaning up
    surface->deleteLater();

    // Stop event processing, move the thread to GUI and make sure it is deleted.
    exit();
    moveToThread(QGuiApplication::instance()->thread());
}


