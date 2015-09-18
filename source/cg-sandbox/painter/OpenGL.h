#pragma once

#include <QOpenGLShader>

class QString;
class QOpenGLTexture;
class QOpenGLShaderProgram;

template <typename OpenGLFunctions>
class OpenGL
{
public:
    OpenGL(OpenGLFunctions & gl);

    void initialize();

    QOpenGLTexture * createTexture2D(const QString & fileName);

    QOpenGLShader * createShader(QOpenGLShader::ShaderType type, const QString & fileName);

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

#include "OpenGL.hpp"
