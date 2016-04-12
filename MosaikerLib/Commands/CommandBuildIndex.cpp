#include "CommandBuildIndex.h"

#include <QDir>
#include <QFile>
#include <QDebug>

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
    ImageIndexer indexer(list);
    QObject::connect(&indexer, SIGNAL(imageIndexed(QString, const QColor&)), this, SLOT(onImageIndexed(QString, const QColor&)));
    indexer.execute();

    mIndexFile.close();
}

void CommandBuildIndex::onImageIndexed(QString imageName, const QColor &color)
{
    qDebug() << "Image " << imageName << " indexed";
}
