#include "FileAssociatedShader.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

FileAssociatedShader::FileAssociatedShader(const QString & fileName, QOpenGLShader * shader)
: FileAssociatedAsset(fileName)
, m_shader(shader)
{
}

QOpenGLShader * FileAssociatedShader::shader()
{
    return m_shader;
}

const QOpenGLShader * FileAssociatedShader::shader() const
{
    return m_shader;
}

void FileAssociatedShader::reload()
{
    m_shader->compileSourceFile(m_fileName);

    for (auto program : m_programs)
    {
        program->link();
    }
}

void FileAssociatedShader::addDependendProgram(QOpenGLShaderProgram * program)
{
    m_programs << program;
}
