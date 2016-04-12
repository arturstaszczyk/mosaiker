#include "CommandBuildIndex.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QDataStream>

#include "ImageIndexer.h"

CommandBuildIndex::CommandBuildIndex(IResourceFinder& finder, QFile& indexFile, QObject* parent)
        : Command(parent)
        , mResourceFinder(finder)
        , mIndexFile(indexFile)
{
    mResourceFinder.addFilter({"*.jpg", "*.png", "*.jpeg"});
}

void CommandBuildIndex::execute()
{
    mResourceFinder.find();
    auto list = mResourceFinder.resourcesList();

    mIndexFile.open(QIODevice::WriteOnly);
    mFileData.clear();

    ImageIndexer indexer(list);
    QObject::connect(&indexer, SIGNAL(imageIndexed(QString, QRgb)), this, SLOT(onImageIndexed(QString, QRgb)));
    indexer.execute();

    mIndexFile.write(mFileData);
    mIndexFile.close();
}

void CommandBuildIndex::onImageIndexed(QString imageName, QRgb color)
{
    qDebug() << "Image " << imageName << " indexed with value " << color;
    QDataStream stream(&mFileData, QIODevice::Append);
    stream << imageName << color;
}
