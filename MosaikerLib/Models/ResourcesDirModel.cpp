#include "ResourcesDirModel.h"

ResourcesDirModel::ResourcesDirModel(QObject *parent) : QObject(parent)
{
}

void ResourcesDirModel::setResourcesDir(QString dirName)
{
    if(mResourcesDir == dirName)
        return;

    mResourcesDir = dirName;
    emit resourcesDirChanged(mResourcesDir);
}

void ResourcesDirModel::setIndexBuilt(bool indexBuilt)
{
    if(mIsIndexBuilt == indexBuilt)
        return;

    mIsIndexBuilt = indexBuilt;
    emit indexBuiltChanged(mIsIndexBuilt);
}
