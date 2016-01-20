#pragma once

#include <QDir>
#include <QObject>
#include <QVector>
#include <QString>

#include "Interfaces/IResourceFinder.h"

class ResourceFinder : public QObject, public IResourceFinder
{
    Q_OBJECT

public:
    explicit ResourceFinder(QString dirName, QObject* parent = nullptr)
        : QObject(parent)
        , mResourcesRoot(dirName)
    {}

    virtual ~ResourceFinder()
    {}

    void addFilter(const QString &filter) override;
    void addFilter(const QStringList& list) override;
    void setFilter(const QString& filter) override;
    void setFilter(const QStringList& list) override;
    void clearFilters() override;

    void find() override;

public:
    quint32 resourcesCount() const override { return mFoundResources.count(); }
    QStringList resourcesList() const override { return mFoundResources; }

private:
    void findFilesInDirectory(const QDir& directory);

private:
    QString mResourcesRoot;
    QStringList mFilters;

    QStringList mFoundResources;
};

