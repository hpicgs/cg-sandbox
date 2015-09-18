#include "DemoPainter32.h"

#include <QOpenGLContext>

#include <cassert>

#include <array>

DemoPainter32::DemoPainter32()
{
}

DemoPainter32::~DemoPainter32()
{
}

void DemoPainter32::initialize(QOpenGLContext * context)
{
    assert(context);

    m_gl = context->versionFunctions<QOpenGLFunctions_3_2_Core>();

    assert(m_gl);

    m_gl->initializeOpenGLFunctions();

    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_textureCoordinateBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vao = new QOpenGLVertexArrayObject();
    m_program = createProgram("data/triangle.vert", "data/triangle.frag");

    m_vao->create();
    m_vao->bind();

    std::array<GLfloat, 6> vertices = {
        -0.8f, -0.8f,
        0.0f, 0.8f,
        0.8f, -0.8f
    };

    std::array<GLfloat, 6> textureCoordinates = {
        0.0f, 0.0f,
        0.5f, 1.0f,
        1.0f, 0.0f
    };

    m_vertexBuffer->create();
    m_vertexBuffer->bind();
    m_vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBuffer->allocate(vertices.data(), sizeof(GLfloat) * vertices.size());

    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 0);
    m_program->enableAttributeArray(0);

    m_textureCoordinateBuffer->create();
    m_textureCoordinateBuffer->bind();
    m_textureCoordinateBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_textureCoordinateBuffer->allocate(textureCoordinates.data(), sizeof(GLfloat) * textureCoordinates.size());

    m_program->setAttributeBuffer(1, GL_FLOAT, 0, 2, 0);
    m_program->enableAttributeArray(1);

    m_vao->release();
    m_program->release();

    m_gl->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void DemoPainter32::deinitialize()
{
    delete m_vertexBuffer;
    delete m_textureCoordinateBuffer;
    delete m_vao;
    delete m_program;
}

const OpenGLContextDescription & DemoPainter32::context() const
{
    static OpenGLContextDescription description = {
        3, 2, true, true, false
    };

    return description;
}

const QStringList & DemoPainter32::extensions() const
{
    static QStringList extensionList;

    return extensionList;
}

void DemoPainter32::paint(CyclicTime::value_type /*time*/)
{
    m_gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();
    m_vao->bind();

    m_gl->glDrawArrays(GL_TRIANGLES, 0, 3);

    m_vao->release();
    m_program->release();
}

void DemoPainter32::resize(const QSize & /*size*/)
{
}
