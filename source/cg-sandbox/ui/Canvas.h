#pragma once

#include <QOpenGLWidget>

class QSurfaceFormat;

class OpenGLContextDescription;
class AbstractPainter;

class Canvas : public QOpenGLWidget
{
public:
    Canvas(const QSurfaceFormat & format, AbstractPainter * painter);
    Canvas(const OpenGLContextDescription & description, AbstractPainter * painter);

    static QSurfaceFormat createFormat(const OpenGLContextDescription & description);

    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

protected:
    AbstractPainter * m_painter;
};
