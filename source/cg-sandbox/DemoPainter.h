#pragma once

#include "painter/AbstractPainter.h"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_2_Core>

#include "painter/OpenGL.h"

class DemoPainter : public AbstractPainter, protected OpenGL
{
public:
    DemoPainter();
    virtual ~DemoPainter();

    virtual void initialize(QOpenGLContext * context) override;
    virtual void deinitialize() override;

    virtual const OpenGLContextDescription & context() const override;
    virtual const QStringList & extensions() const override;

    virtual void paint(CyclicTime::value_type time) override;
    virtual void resize(const QSize & size) override;

protected:
    QOpenGLFunctions_3_2_Core * m_gl;
    QOpenGLBuffer * m_vertexBuffer;
    QOpenGLBuffer * m_textureCoordinateBuffer;
    QOpenGLShaderProgram * m_program;
    QOpenGLVertexArrayObject * m_vao;
};
