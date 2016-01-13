#include "ResourcesDirModel.h"

#include <QDir>
#include <QDebug>

const QString ResourcesDirModel::INDEX_FILE = ".files.index";

ResourcesDirModel::ResourcesDirModel(QObject *parent) : QObject(parent)
{
}

void ResourcesDirModel::setResourcesDir(QString dirName)
{
    if(mResourcesDir == dirName)
        return;

    mResourcesDir = dirName;
    emit resourcesDirChanged(mResourcesDir);

    checkForFileIndex();
}

void ResourcesDirModel::checkForFileIndex()
{
    QDir resourcesDir(mResourcesDir);
    bool doesFileExist = resourcesDir.exists(INDEX_FILE);
    setIndexBuilt(doesFileExist);
}

void ResourcesDirModel::setIndexBuilt(bool indexBuilt)
{
    if(mIsIndexBuilt == indexBuilt)
        return;

    mIsIndexBuilt = indexBuilt;
    emit indexBuiltChanged(mIsIndexBuilt);
}
