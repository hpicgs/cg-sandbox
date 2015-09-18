#include "Canvas.h"

#include <cassert>

#include <QSurfaceFormat>
#include <QOpenGLContext>

#include "util/ChronoTimer.h"
#include "util/CyclicTime.h"

#include "painter/OpenGLContextDescription.h"
#include "painter/AbstractPainter.h"

Canvas::Canvas(const QSurfaceFormat & format, AbstractPainter * painter)
: m_painter(painter)
, m_continuousRepaint(true)
{
    assert(painter != nullptr);

    setFormat(format);
}

Canvas::Canvas(const OpenGLContextDescription & description, AbstractPainter * painter)
: Canvas(createFormat(description), painter)
{
}

Canvas::~Canvas()
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
    if (m_fpsTimer.data())
    {
        const auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(m_fpsTimer->restart()).count();

        if (duration > 0.0f)
        {
            emit(fpsUpdate(1.0f / duration));
        }
    }
    else
    {
        m_fpsTimer.reset(new ChronoTimer());
    }

    m_painter->paint(0);

    if (m_continuousRepaint)
    {
        update();
    }
}

void Canvas::resizeGL(int w, int h)
{
    m_painter->resize(QSize(w, h));
}

void Canvas::setActive(bool on)
{
    if (on)
    {
        m_fpsTimer->reset();
    }
    else
    {

    }
}
