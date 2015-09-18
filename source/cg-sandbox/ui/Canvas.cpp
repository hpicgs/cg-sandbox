#include "Canvas.h"

#include <cassert>

#include <QSurfaceFormat>
#include <QOpenGLContext>

#include "painter/OpenGLContextDescription.h"
#include "painter/AbstractPainter.h"

Canvas::Canvas(const QSurfaceFormat & format, AbstractPainter * painter)
: m_painter(painter)
{
    assert(painter != nullptr);

    setFormat(format);
}

Canvas::Canvas(const OpenGLContextDescription & description, AbstractPainter * painter)
: Canvas(createFormat(description), painter)
{
}

QSurfaceFormat Canvas::createFormat(const OpenGLContextDescription & description)
{
    QSurfaceFormat format;

    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setDepthBufferSize(16);

    format.setMajorVersion(description.majorVersion);
    format.setMinorVersion(description.minorVersion);
    format.setProfile(description.coreFlag ? QSurfaceFormat::CoreProfile : QSurfaceFormat::CompatibilityProfile);
    format.setOption(QSurfaceFormat::DebugContext, description.debugFlag);
    format.setOption(QSurfaceFormat::DeprecatedFunctions, !description.forwardFlag);

    return format;
}

void Canvas::initializeGL()
{
    m_painter->initialize(context());
}

void Canvas::paintGL()
{
    m_painter->paint(0);
}

void Canvas::resizeGL(int w, int h)
{
    m_painter->resize(QSize(w, h));
}
