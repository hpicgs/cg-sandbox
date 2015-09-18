
#include "OpenGL.h"

#include <QString>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

OpenGL::OpenGL()
{
}

QOpenGLTexture * OpenGL::createTexture2D(const QString & fileName)
{
    QImage image(fileName);

    QOpenGLTexture * texture = new QOpenGLTexture(image.mirrored(), QOpenGLTexture::DontGenerateMipMaps);

    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
    texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);

    return texture;
}

QOpenGLShader * OpenGL::createShader(QOpenGLShader::ShaderType type, const QString & fileName)
{
    QOpenGLShader * shader = new QOpenGLShader(type);

    shader->compileSourceFile(fileName);

    return shader;
}

QOpenGLShaderProgram * OpenGL::createProgram(const QString & computeShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    program->addShader(createShader(QOpenGLShader::Compute, computeShaderFileName));
    program->link();

    return program;
}

QOpenGLShaderProgram * OpenGL::createProgram(
    const QString & vertexShaderFileName
,   const QString & fragmentShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    program->addShader(createShader(QOpenGLShader::Vertex, vertexShaderFileName));
    program->addShader(createShader(QOpenGLShader::Fragment, fragmentShaderFileName));
    program->link();

    return program;
}

QOpenGLShaderProgram * OpenGL::createProgram(
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

QOpenGLShaderProgram * OpenGL::createProgram(
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

QOpenGLShaderProgram * OpenGL::createProgram(
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
