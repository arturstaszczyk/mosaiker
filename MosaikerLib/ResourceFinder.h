﻿#pragma once

#include <QVector>
#include <QString>

class ResourceFinder
{
public:
    ResourceFinder(QString dirName)
        : mResourcesRoot(dirName)
    {}

    ~ResourceFinder()
    {}

    void addFilter(const QString filter);
    void addFilter(const QStringList list);
    void clearFilters();

    void find();

public:
    quint32 resourcesCount() const { return mFoundResources.count(); }

private:
    void findFilesInDirectory(const QDir& directory);

private:
    QString mResourcesRoot;
    QStringList mFilters;

    QStringList mFoundResources;
};

