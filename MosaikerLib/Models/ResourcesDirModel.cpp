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
