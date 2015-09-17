#pragma once

#include <qgl.h>

#include <QString>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

template <typename OpenGLFunctions>
class OpenGL
{
public:
    OpenGL(OpenGLFunctions & gl);

    QOpenGLTexture * createTexture(const QString & fileName);

    QOpenGLShaderProgram * createProgram(const QString & computeShaderFileName);

    QOpenGLShaderProgram * createProgram(
        const QString & vertexShaderFileName
    ,   const QString & fragmentShaderFileName);

    QOpenGLShaderProgram * createProgram(
        const QString & vertexShaderFileName
    ,   const QString & geometryShaderFileName
    ,   const QString & fragmentShaderFileName);

    QOpenGLShaderProgram * createProgram(
        const QString & vertexShaderFileName
    ,   const QString & tessellationControlShaderFileName
    ,   const QString & tessellationEvaluationShaderFileName
    ,   const QString & fragmentShaderFileName);

    QOpenGLShaderProgram * createProgram(
        const QString & vertexShaderFileName
    ,   const QString & tessellationControlShaderFileName
    ,   const QString & tessellationEvaluationShaderFileName
    ,   const QString & geometryShaderFileName
    ,   const QString & fragmentShaderFileName);

protected:
    OpenGLFunctions & m_gl;
};
