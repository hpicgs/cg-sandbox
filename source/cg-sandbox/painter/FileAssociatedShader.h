#pragma once

#include <QList>

#include "FileAssociatedAsset.h"

class QOpenGLShader;
class QOpenGLShaderProgram;

class FileAssociatedShader : public FileAssociatedAsset
{
public:
    FileAssociatedShader(const QString & fileName, QOpenGLShader * shader);

    QOpenGLShader * shader();
    const QOpenGLShader * shader() const;

    virtual void reload() override;

    void addDependendProgram(QOpenGLShaderProgram * program);
protected:
    QOpenGLShader * m_shader;
    QList<QOpenGLShaderProgram *> m_programs;
};
