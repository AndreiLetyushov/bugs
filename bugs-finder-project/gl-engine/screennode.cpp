#include "screennode.h"

ScreenNode::ScreenNode(QSharedPointer<ScreenNode> parent)
    : m_parentNode(parent)
{

}

ScreenNode::~ScreenNode()
{

}

void ScreenNode::addChild(QSharedPointer<ScreenNode> child)
{
    m_childNodes << child;
}

void ScreenNode::setParent(QSharedPointer<ScreenNode> parent)
{
    m_parentNode = parent;
}

void ScreenNode::render(QOpenGLShaderProgram &program)
{
    program.setUniformValue("matrix", m_modelview * m_parentNode->modelview());
    program.setUniformValue("projection", m_projection * m_parentNode->projection());
    program.setUniformValue("texture", m_texture->textureId());
    program.setUniformValue("textureTransformation", m_textureTransformation);

    QVector <QVector3D> vertex = m_coordsRelativeScene.getCoords();
    QVector <QVector3D> texCoords = m_coordsRelativePresssheet.getCoords();

    program.setAttributeArray("vertex", vertex.constData());
    program.setAttributeArray("aTexCoords", texCoords.constData());

    glColor3f(1.0, 0.0, 0.0);

    glDrawArrays(GL_QUADS, 0, 4);

    for(auto childNode : m_childNodes)
        childNode->render(program);
}

void ScreenNode::clear()
{
    for(auto node: m_childNodes)
        node->clear();

    m_childNodes.clear();
}

void ScreenNode::setStartPoint(qreal x, qreal y, qreal z, ScreenNode::TypeOfCoords type)
{
    switch(type) {
    case ScreenNode::TypeOfCoords::RelativePresssheet: {
        m_coordsRelativePresssheet.setPoint1(QVector3D(x, y, z));
        m_coordsRelativePresssheet.setPoint1(QVector3D(x, 1, z));
        m_coordsRelativePresssheet.setPoint1(QVector3D(1, 1, z));
        m_coordsRelativePresssheet.setPoint1(QVector3D(1, y, z));
        break;
    }
    case ScreenNode::TypeOfCoords::RelativeScene: {
        m_coordsRelativeScene.setPoint1(QVector3D(x, y, z));
        break;
    }
    default:
        break;
    }

}

QVector3D ScreenNode::startPoint(ScreenNode::TypeOfCoords type)
{
    switch(type) {
    case ScreenNode::TypeOfCoords::RelativePresssheet:
        return m_coordsRelativePresssheet.point1();
    case ScreenNode::TypeOfCoords::RelativeScene:
        return m_coordsRelativeScene.point1();
    default:
        return QVector3D(0, 0, 0);
    }
}

void ScreenNode::setSize(qreal width, qreal height)
{
    m_sizeRelativeScene.setWidth(width);
    m_sizeRelativeScene.setHeight(height);

    updateCoords();
}

void ScreenNode::updateCoords()
{
    m_coordsRelativeScene.calcAllPoints(m_sizeRelativeScene.width(), m_sizeRelativeScene.height());
}

QMatrix4x4 ScreenNode::projection() const
{
    return m_projection;
}

QMatrix4x4 ScreenNode::modelview() const
{
    return m_modelview;
}

QOpenGLTexture *ScreenNode::texture() const
{
    return m_texture;
}

void ScreenNode::setTexture(QOpenGLTexture *texture)
{
    m_texture = texture;
    m_texture->bind(m_texture->textureId());
}


MainScene::MainScene()
{
    m_vshader = new QOpenGLShader(QOpenGLShader::Vertex, &m_program);
    m_fshader = new QOpenGLShader(QOpenGLShader::Fragment, &m_program);

    m_vshader->compileSourceFile(QString(":/shaders/shader.vert"));
    m_fshader->compileSourceFile(QString(":/shaders/shader.frag"));

    m_program.addShader(m_vshader);
    m_program.addShader(m_fshader);

    m_program.link();
    m_program.bind();

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

    m_modelview.scale(2);
    m_modelview.translate(-0.5f, -0.5f, 0.0f);

    setStartPoint(0.0, 0.0, 0.0, TypeOfCoords::RelativeScene);
    setSize(1.0, 1.0);
}

MainScene::~MainScene()
{
    m_program.release();
}

void MainScene::render()
{
    glDepthMask(true);
    glClearColor(0.7f, 0.5f, 0.5f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); // alpha blending
    glDisable(GL_DEPTH_TEST);

    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    m_program.setUniformValue("matrix", m_modelview);
    m_program.setUniformValue("projection", m_projection);

    m_program.enableAttributeArray("vertex");
    m_program.enableAttributeArray("aTexCoords");

    m_program.setUniformValue("texture", m_texture->textureId());
    m_program.setUniformValue("textureTransformation", m_textureTransformation);

    QVector <QVector3D> vertex = m_coordsRelativeScene.getCoords();
    QVector <QVector3D> texCoords = m_coordsRelativePresssheet.getCoords();

    m_program.setAttributeArray("vertex", vertex.constData());
    m_program.setAttributeArray("aTexCoords", texCoords.constData());

    glDrawArrays(GL_QUADS, 0, 4);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

    for(auto childNode : m_childNodes)
        childNode->render(m_program);

    glDisable(GL_CULL_FACE);
    m_program.disableAttributeArray("vertex");
    m_program.disableAttributeArray("aTexCoords");
}

FixedScreenNode::FixedScreenNode(QSharedPointer<ScreenNode> parent)
    : ScreenNode(parent)
{
    m_parentNode = parent;

    m_coordsRelativePresssheet.setPoint1(QVector3D(0.0, 0.0, 0.0));
    m_coordsRelativePresssheet.setPoint2(QVector3D(0.0, 1.0, 0.0));
    m_coordsRelativePresssheet.setPoint3(QVector3D(1.0, 1.0, 0.0));
    m_coordsRelativePresssheet.setPoint4(QVector3D(1.0, 0.0, 0.0));
}


MovableScreenNode::MovableScreenNode(QSharedPointer<ScreenNode> parent)
    : ScreenNode(parent)
{
}
