#include "DemoPainter21.h"

#include <QOpenGLContext>

#include <cassert>

#include <array>

DemoPainter21::DemoPainter21()
{
}

DemoPainter21::~DemoPainter21()
{
}

void DemoPainter21::initialize(QOpenGLContext * context)
{
    assert(context);

    m_gl = context->versionFunctions<QOpenGLFunctions_2_1>();

    assert(m_gl);

    m_gl->initializeOpenGLFunctions();

    m_gl->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void DemoPainter21::deinitialize()
{
}

const OpenGLContextDescription & DemoPainter21::context() const
{
    static OpenGLContextDescription description = {
        2, 1, false, false, false
    };

    return description;
}

const QStringList & DemoPainter21::extensions() const
{
    static QStringList extensionList;

    return extensionList;
}

void DemoPainter21::paint(CyclicTime::value_type /*time*/)
{
    m_gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_gl->glBegin(GL_TRIANGLES);
        m_gl->glColor3f(0.0f, 0.0f, 0.0f);
        m_gl->glVertex2f(-0.8f, -0.8f);

        m_gl->glColor3f(0.5f, 1.0f, 0.0f);
        m_gl->glVertex2f(0.0f, 0.8f);

        m_gl->glColor3f(1.0f, 0.0f, 0.0f);
        m_gl->glVertex2f(0.8, -0.8f);
    m_gl->glEnd();
}

void DemoPainter21::resize(const QSize & size)
{
    m_gl->glViewport(0, 0, size.width(), size.height());
}
