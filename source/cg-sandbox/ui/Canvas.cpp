#include "Canvas.h"

#include <cassert>

#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QDebug>
#include <QMouseEvent>

#include "util/ChronoTimer.h"
#include "util/CyclicTime.h"

#include "painter/OpenGLContextDescription.h"
#include "painter/AbstractPainter.h"
#include "painter/FileAssociatedAsset.h"

Canvas::Canvas(const QSurfaceFormat & format, AbstractPainter * painter)
: m_painter(painter)
, m_active(false)
, m_continuousRepaint(true)
{
    assert(painter != nullptr);

    setFormat(format);
    setFocusPolicy(Qt::TabFocus);
    setMouseTracking(true);
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
    const auto currentFormat = format();

    qDebug() << QString("Created OpenGL Context with Version %1.%2").arg(currentFormat.version().first).arg(currentFormat.version().second).toStdString().c_str();

    m_painter->initialize(context());
    m_virtualTime.reset(new CyclicTime(10.0));

    if (!m_active)
    {
        m_virtualTime->pause();
    }
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

    const auto time = m_virtualTime->normalizedTime();

    emit(timeUpdate(time));

    FileAssociatedAsset::process();

    m_painter->paint(time);

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
    m_active = on;

    if (m_active)
    {
        if (m_fpsTimer)
        {
            m_fpsTimer->reset();
        }

        if (m_virtualTime)
        {
            m_virtualTime->pause();
        }
    }
    else
    {
        if (m_virtualTime)
        {
            m_virtualTime->pause();
        }
    }
}

void Canvas::keyPressEvent(QKeyEvent   * event)
{
    Q_UNUSED(event);
}

void Canvas::keyReleaseEvent(QKeyEvent   * event)
{
    Q_UNUSED(event);
}

void Canvas::mouseMoveEvent(QMouseEvent * event)
{
    emit(mouseUpdate(event->pos()));
}

void Canvas::mousePressEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
}

void Canvas::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
}

void Canvas::mouseDoubleClickEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
}

void Canvas::wheelEvent(QWheelEvent * event)
{
    Q_UNUSED(event);
}
