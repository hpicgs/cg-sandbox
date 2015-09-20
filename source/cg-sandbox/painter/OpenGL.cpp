
#include "OpenGL.h"

#include <QString>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

#include "FileAssociatedShader.h"

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

FileAssociatedShader * OpenGL::createShader(QOpenGLShader::ShaderType type, const QString & fileName)
{
    QOpenGLShader * shader = new QOpenGLShader(type);

    FileAssociatedShader * shaderAsset = new FileAssociatedShader(fileName, shader);
    shaderAsset->reload();

    return shaderAsset;
}

void OpenGL::addShader(QOpenGLShaderProgram * program, FileAssociatedShader * shaderAsset)
{
    QOpenGLShader * shader = shaderAsset->shader();

    program->addShader(shader);
    shaderAsset->addDependendProgram(program);
}

QOpenGLShaderProgram * OpenGL::createProgram(const QString & computeShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    addShader(program, createShader(QOpenGLShader::Compute, computeShaderFileName));
    program->link();

    return program;
}

QOpenGLShaderProgram * OpenGL::createProgram(
    const QString & vertexShaderFileName
,   const QString & fragmentShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    addShader(program, createShader(QOpenGLShader::Vertex, vertexShaderFileName));
    addShader(program, createShader(QOpenGLShader::Fragment, fragmentShaderFileName));
    program->link();

    return program;
}

QOpenGLShaderProgram * OpenGL::createProgram(
    const QString & vertexShaderFileName
,   const QString & geometryShaderFileName
,   const QString & fragmentShaderFileName)
{
    QOpenGLShaderProgram * program = new QOpenGLShaderProgram();

    addShader(program, createShader(QOpenGLShader::Vertex, vertexShaderFileName));
    addShader(program, createShader(QOpenGLShader::Geometry, geometryShaderFileName));
    addShader(program, createShader(QOpenGLShader::Fragment, fragmentShaderFileName));
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

    addShader(program, createShader(QOpenGLShader::Vertex, vertexShaderFileName));
    addShader(program, createShader(QOpenGLShader::TessellationControl, tessellationControlShaderFileName));
    addShader(program, createShader(QOpenGLShader::TessellationEvaluation, tessellationEvaluationShaderFileName));
    addShader(program, createShader(QOpenGLShader::Fragment, fragmentShaderFileName));
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

    addShader(program, createShader(QOpenGLShader::Vertex, vertexShaderFileName));
    addShader(program, createShader(QOpenGLShader::TessellationControl, tessellationControlShaderFileName));
    addShader(program, createShader(QOpenGLShader::TessellationEvaluation, tessellationEvaluationShaderFileName));
    addShader(program, createShader(QOpenGLShader::Geometry, geometryShaderFileName));
    addShader(program, createShader(QOpenGLShader::Fragment, fragmentShaderFileName));
    program->link();

    return program;
}
