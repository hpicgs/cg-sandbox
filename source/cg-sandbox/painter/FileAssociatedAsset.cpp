#include "FileAssociatedAsset.h"

#include <QFileSystemWatcher>

namespace
{
    QFileSystemWatcher * watcher = nullptr;
}

QHash<QString, FileAssociatedAsset *> FileAssociatedAsset::s_instances;

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
    if (s_instances.empty())
    {
        watcher = new QFileSystemWatcher();
        QObject::connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(reload(QString)));
    }

    s_instances.insert(m_fileName, this);
    watcher->addPath(m_fileName);
}

void FileAssociatedAsset::deregisterInstance()
{
    watcher->removePath(m_fileName);
    s_instances.remove(m_fileName);

    if (s_instances.empty())
    {
        delete watcher;
    }
}

void FileAssociatedAsset::reloadAll()
{
    for (FileAssociatedAsset * asset : s_instances)
    {
        asset->reload();
    }
}

void FileAssociatedAsset::reload(const QString & fileName)
{
    if (s_instances.contains(fileName))
    {
        s_instances.value(fileName)->reload();
    }
}
