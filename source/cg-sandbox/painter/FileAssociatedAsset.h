#pragma once

#include <QHash>
#include <QObject>
#include <QString>

class FileAssociatedAsset : public QObject
{
    Q_OBJECT

public:
    FileAssociatedAsset(const QString & fileName);
    virtual ~FileAssociatedAsset();

    void registerInstance();
    void deregisterInstance();

    virtual void reload() = 0;

    static void process();
    static void forceReload();

public slots:
    void invalidate(const QString & fileName);

protected:
    QString m_fileName;
};
