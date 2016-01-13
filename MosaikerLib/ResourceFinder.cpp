#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include "ResourceFinder.h"
#include "Exceptions.h"

void ResourceFinder::addFilter(const QString& filter)
{
    mFilters.append(filter);
}

void ResourceFinder::addFilter(const QStringList& list)
{
    mFilters.append(list);
}

void ResourceFinder::setFilter(const QString& filter)
{
    mFilters.clear();
    mFilters.append(filter);
}

void ResourceFinder::setFilter(const QStringList& list)
{
    mFilters.clear();
    mFilters.append(list);
}

void ResourceFinder::clearFilters()
{
    mFilters.clear();
}

void ResourceFinder::find()
{
    mFoundResources.clear();

    QDir rootResources(mResourcesRoot);
    if(!rootResources.exists())
        throw PathDoNotExists();

    findFilesInDirectory(rootResources);
}

void ResourceFinder::findFilesInDirectory(const QDir& directory)
{
    QFileInfoList directories = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfo dirInfo;
    foreach(dirInfo, directories)
        findFilesInDirectory(dirInfo.filePath());

    QFileInfoList files = directory.entryInfoList(mFilters, QDir::Files);
    QFileInfo fileInfo;
    foreach(fileInfo, files)
        mFoundResources.append(fileInfo.filePath());
}
