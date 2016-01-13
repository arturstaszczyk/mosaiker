#ifndef RESOURCESDIRMODEL_H
#define RESOURCESDIRMODEL_H

#include <QObject>

class ResourcesDirModel : public QObject
{
    Q_OBJECT
public:
    explicit ResourcesDirModel(QObject *parent = 0);

    Q_PROPERTY(QString resourcesDir READ resourcesDir WRITE setResourcesDir NOTIFY resourcesDirChanged)


public slots:
    QString resourcesDir() const { return mResourcesDir; }
    void setResourcesDir(QString dirName);

signals:
    void resourcesDirChanged(QString dirName);

private:
    QString mResourcesDir;

};

#endif // RESOURCESDIRMODEL_H
