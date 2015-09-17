
#pragma once

#include <QList>
#include <QSize>

#include "OpenGLContextDescription.h"

class QStringList;
class QOpenGLShaderProgram;

class Camera;


class AbstractPainter
{
public:
    AbstractPainter();
    virtual ~AbstractPainter();

    virtual const OpenGLContextDescription & context() const;
    virtual const QStringList & extensions() const;

    void setCamera(Camera * camera);
    Camera * camera();

    virtual bool initialize() = 0;

    virtual void paint(float timef) = 0;
    virtual void resize(int width, int height) = 0;

    virtual void update() = 0;
    virtual void update(const QList<QOpenGLShaderProgram *> & programs) = 0;

protected:
    Camera * m_camera;
};
