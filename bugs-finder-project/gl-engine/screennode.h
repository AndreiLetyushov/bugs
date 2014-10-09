#ifndef SCREENNODE_H
#define SCREENNODE_H

#include <QtGlobal>
#include <QUrl>
#include <QOpenGLTexture>
#include <QSharedPointer>
#include <QOpenGLShaderProgram>

#include "nodecoords.h"
#include "nodesize.h"



class ScreenNode
{
public:

    enum class TypeOfCoords {
        RelativePresssheet,
        RelativeScene
    };

    explicit ScreenNode(QSharedPointer<ScreenNode> parent = QSharedPointer<ScreenNode>());
    virtual ~ScreenNode();


    void addChild(QSharedPointer<ScreenNode> child);
    void setParent(QSharedPointer<ScreenNode> parent);

    void render(QOpenGLShaderProgram &program);
    void clear();

    void setStartPoint(qreal x, qreal y, qreal z, TypeOfCoords type);
    QVector3D startPoint(TypeOfCoords type);

    void setSize(qreal width, qreal height);

    QOpenGLTexture *texture() const;
    void setTexture(QOpenGLTexture *texture);

    QMatrix4x4 parentViewMatrix();
    QMatrix4x4 parentProjectMatrix();

    void rotate(float angle, float x, float y, float z = 0.0f);

    QMatrix4x4 modelview() const;
    QMatrix4x4 projection() const;

protected:

    void updateCoords();

    qint32 m_ratation;

    NodeSize m_sizeRelativePresssheet;
    NodeSize m_sizeRelativeScene;

    NodeCoords m_coordsRelativePresssheet;
    NodeCoords m_coordsRelativeScene;

    QOpenGLTexture *m_texture;

    QMatrix4x4 m_modelview;
    QMatrix4x4 m_projection;

    QTransform m_textureTransformation;

    QSharedPointer<ScreenNode> m_parentNode;
    QList <QSharedPointer<ScreenNode> > m_childNodes;
};




class FixedScreenNode: public ScreenNode
{
public:
    FixedScreenNode(QSharedPointer<ScreenNode> parent = QSharedPointer<ScreenNode>());

private:
};

class MovableScreenNode: public ScreenNode
{
public:
    MovableScreenNode(QSharedPointer<ScreenNode> parent = QSharedPointer<ScreenNode>());
    void explodeNode();
};


class MainScene: public ScreenNode
{
public:
    MainScene();
    ~MainScene();

    void render();



private:
    QOpenGLShaderProgram m_program;

    QOpenGLShader *m_vshader;
    QOpenGLShader *m_fshader;
};
#endif // SCREENNODE_H
