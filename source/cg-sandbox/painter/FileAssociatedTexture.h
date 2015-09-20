#pragma once

#include <QList>

#include "FileAssociatedAsset.h"

class QOpenGLTexture;

class FileAssociatedTexture : public FileAssociatedAsset
{
public:
    FileAssociatedTexture(const QString & fileName, QOpenGLTexture * texture);

    QOpenGLTexture * texture();
    const QOpenGLTexture * texture() const;

    virtual void reload() override;
protected:
    QOpenGLTexture * m_texture;
};
