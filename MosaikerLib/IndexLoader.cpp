#include "IndexLoader.h"

#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QDataStream>

#include "Exceptions.h"

IndexLoader::IndexLoader(QString indexFileNmae, QObject *parent)
    : QObject(parent)
    , mIndexFileName(indexFileNmae)
{

}

void IndexLoader::loadIndex()
{
    QFile indexFile(mIndexFileName);
    if(!indexFile.exists())
        throw PathDoNotExists();

    indexFile.open(QIODevice::ReadOnly);
    QDataStream stream(&indexFile);

    while(!stream.atEnd())
    {
        QString fileName;
        quint32 index;
        stream >> fileName >> index;
        mFileIndex.append({index, fileName});
    }
}

QString IndexLoader::closestFileNameByIndex(quint32 index)
{
    quint32 distance = 10e5;
    IndexLoader::Index currentIndex;
    IndexLoader::Index foundIndex;
    foreach(currentIndex, mFileIndex)
    {
        quint32 actDistance = currentIndex.distanceToIndex(index);
        if(actDistance < distance)
        {
            foundIndex = currentIndex;
            distance = actDistance;
        }
    }

    return foundIndex.fileName;
}
