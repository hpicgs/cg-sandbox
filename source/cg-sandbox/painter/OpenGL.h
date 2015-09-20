#pragma once

#include <QOpenGLShader>

class QString;
class QOpenGLTexture;
class QOpenGLShaderProgram;

class FileAssociatedShader;

class OpenGL
{
public:
    OpenGL();

    QOpenGLTexture * createTexture2D(const QString & fileName);

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
    FileAssociatedShader * createShader(QOpenGLShader::ShaderType type, const QString & fileName);

    void addShader(QOpenGLShaderProgram * program, FileAssociatedShader * shaderAsset);
};
