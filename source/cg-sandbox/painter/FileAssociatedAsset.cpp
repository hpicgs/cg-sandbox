#include "FileAssociatedAsset.h"

#include <QFileSystemWatcher>
#include <QOpenGLContext>
#include <QSet>
#include <QDebug>

namespace
{
    QFileSystemWatcher * watcher = nullptr;

    QHash<QOpenGLContext *, QSet<FileAssociatedAsset *>> invalidAssets;
    QHash<QOpenGLContext *, QHash<QString, FileAssociatedAsset *>> assets;

    bool isEmpty(const QHash<QOpenGLContext *, QHash<QString, FileAssociatedAsset *>> & hash)
    {
        for (const auto & value : hash)
        {
            if (!value.empty())
            {
                return false;
            }
        }

        return true;
    }
}

FileAssociatedAsset::FileAssociatedAsset(const QString & fileName)
: m_fileName(fileName)
{
    registerInstance();
}

FileAssociatedAsset::~FileAssociatedAsset()
{
    deregisterInstance();
}

void FileAssociatedAsset::registerInstance()
{
    if (isEmpty(assets))
    {
        watcher = new QFileSystemWatcher();
        QObject::connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(invalidate(QString)));
    }

    auto & instances = assets[QOpenGLContext::currentContext()];
    instances.insert(m_fileName, this);
    watcher->addPath(m_fileName);
}

void FileAssociatedAsset::deregisterInstance()
{
    watcher->removePath(m_fileName);

    auto & instances = assets[QOpenGLContext::currentContext()];
    instances.remove(m_fileName);

    if (isEmpty(assets))
    {
        delete watcher;
    }
}

void FileAssociatedAsset::process()
{
    for (auto asset : invalidAssets[QOpenGLContext::currentContext()])
    {
        asset->reload();
    }

    invalidAssets[QOpenGLContext::currentContext()].clear();
}

void FileAssociatedAsset::forceReload()
{
    auto context = QOpenGLContext::currentContext();
    for (FileAssociatedAsset * asset : assets.value(context))
    {
        asset->reload();
    }

    invalidAssets[context].clear();
}

void FileAssociatedAsset::invalidate(const QString & fileName)
{
    for (const auto context : assets.keys())
    {
        if (assets.value(context).contains(fileName))
        {
            invalidAssets[context].insert(assets.value(context).value(fileName));
        }
    }
}
