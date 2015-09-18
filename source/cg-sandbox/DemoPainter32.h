#pragma once

#include "painter/AbstractPainter.h"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_2_Core>

#include "painter/OpenGL.h"

class DemoPainter32 : public AbstractPainter, protected OpenGL
{
public:
    DemoPainter32();
    virtual ~DemoPainter32();

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
