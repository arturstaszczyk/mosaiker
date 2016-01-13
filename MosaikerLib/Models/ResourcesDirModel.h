#ifndef RESOURCESDIRMODEL_H
#define RESOURCESDIRMODEL_H

#include <QObject>

class ResourcesDirModel : public QObject
{
    Q_OBJECT

public:
    static const QString INDEX_FILE;

public:
    explicit ResourcesDirModel(QObject *parent = 0);

    Q_PROPERTY(QString resourcesDir READ resourcesDir NOTIFY resourcesDirChanged)
    Q_PROPERTY(bool isIndexBuilt MEMBER mIsIndexBuilt WRITE setIndexBuilt NOTIFY indexBuiltChanged)

    QString resourcesDir() const { return mResourcesDir; }

public slots:
    void setResourcesDir(QString dirName);
    void setIndexBuilt(bool isIndexBuilt);

signals:
    void resourcesDirChanged(QString dirName);
    void indexBuiltChanged(bool indexBuilt);

private:
    void checkForFileIndex();

private:
    QString mResourcesDir;
    bool mIsIndexBuilt;

};

#endif // RESOURCESDIRMODEL_H
