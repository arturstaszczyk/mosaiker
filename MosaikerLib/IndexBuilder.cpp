#include "IndexBuilder.h"

#include <QDebug>
#include <QFile>
#include <QDataStream>

IndexBuilder::IndexBuilder(QString indexFilename, QObject *parent)
    : QObject(parent)
    , mIndexFilename(indexFilename)
{

}

void IndexBuilder::addIndexForFilename(quint32 index, QString filename)
{
    qDebug() << "Image " << filename << " indexed with value " << index;
    QDataStream stream(&mFileData, QIODevice::Append);
    stream << filename << index;
}

void IndexBuilder::save()
{
    QFile indexFile(mIndexFilename);
    indexFile.open(QIODevice::WriteOnly);
    indexFile.write(mFileData);
    indexFile.close();
    qDebug() << "Written file " << mIndexFilename;
}
