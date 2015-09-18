
#pragma once

#include <QSize>
#include <QStringList>

#include "OpenGLContextDescription.h"
#include "util/CyclicTime.h"

class QOpenGLContext;

class Camera;

class AbstractPainter
{
public:
    AbstractPainter();
    virtual ~AbstractPainter();

    void setCamera(Camera * camera);
    Camera * camera();

    virtual void initialize(QOpenGLContext * context) = 0;
    virtual void deinitialize() = 0;

    virtual const OpenGLContextDescription & context() const = 0;
    virtual const QStringList & extensions() const = 0;

    virtual void paint(CyclicTime::value_type time) = 0;
    virtual void resize(const QSize & size) = 0;

protected:
    Camera * m_camera;
};
