
#pragma once

#include "OpenGL.h"

#include <qgl.h>

#include <QString>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

template <typename OpenGLFunctions>
OpenGL<OpenGLFunctions>::OpenGL(OpenGLFunctions & gl)
: m_gl(gl)
{
}

template <typename OpenGLFunctions>
void OpenGL<OpenGLFunctions>::initialize()
{
    m_gl.initializeOpenGLFunctions();
}

template <typename OpenGLFunctions>
QOpenGLTexture * OpenGL<OpenGLFunctions>::createTexture2D(const QString & fileName)
{
    QImage image(fileName);

    QOpenGLTexture * texture = new QOpenGLTexture(image.mirrored(), QOpenGLTexture::DontGenerateMipMaps);

    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
    texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);

    texture->create();
}

template <typename OpenGLFunctions>
QOpenGLShader * OpenGL<OpenGLFunctions>::createShader(QOpenGLShader::ShaderType type, const QString & fileName)
{
    QOpenGLShader * shader = new QOpenGLShader(type);

    shader->compileSourceFile(fileName);

    return shader;
}

template <typename OpenGLFunctions>
QOpenGLShaderProgram * OpenGL<OpenGLFunctions>::createProgram(const QString & computeShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    program->addShader(createShader(QOpenGLShader::Compute, computeShaderFileName));
    program->link();

    return program;
}

template <typename OpenGLFunctions>
QOpenGLShaderProgram * OpenGL<OpenGLFunctions>::createProgram(
    const QString & vertexShaderFileName
,   const QString & fragmentShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    program->addShader(createShader(QOpenGLShader::Vertex, vertexShaderFileName));
    program->addShader(createShader(QOpenGLShader::Fragment, fragmentShaderFileName));
    program->link();

    return program;
}

template <typename OpenGLFunctions>
QOpenGLShaderProgram * OpenGL<OpenGLFunctions>::createProgram(
    const QString & vertexShaderFileName
,   const QString & geometryShaderFileName
,   const QString & fragmentShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    program->addShader(createShader(QOpenGLShader::Vertex, vertexShaderFileName));
    program->addShader(createShader(QOpenGLShader::Geometry, geometryShaderFileName));
    program->addShader(createShader(QOpenGLShader::Fragment, fragmentShaderFileName));
    program->link();

    return program;
}

template <typename OpenGLFunctions>
QOpenGLShaderProgram * OpenGL<OpenGLFunctions>::createProgram(
    const QString & vertexShaderFileName
,   const QString & tessellationControlShaderFileName
,   const QString & tessellationEvaluationShaderFileName
,   const QString & fragmentShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    program->addShader(createShader(QOpenGLShader::Vertex, vertexShaderFileName));
    program->addShader(createShader(QOpenGLShader::TessellationControl, tessellationControlShaderFileName));
    program->addShader(createShader(QOpenGLShader::TessellationEvaluation, tessellationEvaluationShaderFileName));
    program->addShader(createShader(QOpenGLShader::Fragment, fragmentShaderFileName));
    program->link();

    return program;
}

template <typename OpenGLFunctions>
QOpenGLShaderProgram * OpenGL<OpenGLFunctions>::createProgram(
    const QString & vertexShaderFileName
,   const QString & tessellationControlShaderFileName
,   const QString & tessellationEvaluationShaderFileName
,   const QString & geometryShaderFileName
,   const QString & fragmentShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    program->addShader(createShader(QOpenGLShader::Vertex, vertexShaderFileName));
    program->addShader(createShader(QOpenGLShader::TessellationControl, tessellationControlShaderFileName));
    program->addShader(createShader(QOpenGLShader::TessellationEvaluation, tessellationEvaluationShaderFileName));
    program->addShader(createShader(QOpenGLShader::Geometry, geometryShaderFileName));
    program->addShader(createShader(QOpenGLShader::Fragment, fragmentShaderFileName));
    program->link();

    return program;
}
