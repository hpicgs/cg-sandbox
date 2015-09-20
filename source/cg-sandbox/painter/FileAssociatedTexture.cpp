#include "FileAssociatedTexture.h"

#include <QOpenGLTexture>

FileAssociatedTexture::FileAssociatedTexture(const QString & fileName, QOpenGLTexture * texture)
: FileAssociatedAsset(fileName)
, m_texture(texture)
{
}

QOpenGLTexture * FileAssociatedTexture::texture()
{
    return m_texture;
}

const QOpenGLTexture * FileAssociatedTexture::texture() const
{
    return m_texture;
}

void FileAssociatedTexture::reload()
{
    QImage image(m_fileName);

    m_texture->setData(image.mirrored(), QOpenGLTexture::DontGenerateMipMaps);
}
