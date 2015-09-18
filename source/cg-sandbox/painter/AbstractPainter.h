
#pragma once

#include <QSize>
#include <QStringList>

#include "OpenGLContextDescription.h"
#include "util/CyclicTime.h"

class QOpenGLContext;

class Camera;
class Navigation;

class AbstractPainter
{
public:
    AbstractPainter();
    virtual ~AbstractPainter();

    virtual Camera * createCamera();
    virtual Navigation * createNavigation();

    Camera * camera();
    Navigation * navigation();

    virtual void initialize(QOpenGLContext * context) = 0;
    virtual void deinitialize() = 0;

    virtual const OpenGLContextDescription & context() const = 0;
    virtual const QStringList & extensions() const = 0;

    virtual void paint(CyclicTime::value_type time) = 0;
    virtual void resize(const QSize & size) = 0;

protected:
    QScopedPointer<Camera> m_camera;
    QScopedPointer<Navigation> m_navigation;
};
