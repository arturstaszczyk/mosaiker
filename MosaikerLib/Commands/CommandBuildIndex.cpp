#include "CommandBuildIndex.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QColor>
#include <QDataStream>

#include "ImageIndexer.h"

static int imageConuter = 0;

CommandBuildIndex::CommandBuildIndex(IResourceFinder* finder, QString& indexFileName,
                                     ResourcesDirModel* resourcesDirModel, QObject* parent)
        : Command(COMMAND_NAME(CommandBuildIndex), parent)
        , mResourceFinder(finder)
        , mIndexFileName(indexFileName)
        , mResourcesDirModel(resourcesDirModel)
{
    dynamic_cast<QObject*>(mResourceFinder)->setParent(this);
    mResourceFinder->addFilter({"*.jpg", "*.png", "*.jpeg"});
}

void CommandBuildIndex::execute()
{
    mResourcesDirModel->setIndexBuilding(true);
    mResourceFinder->find();
    auto list = mResourceFinder->resourcesList();
    emit resourcesCount(list.count());

    mFileData.clear();

    imageConuter = 0;

    QThread* indexer = new ImageIndexer(list, this);
    connect(indexer, SIGNAL(imageIndexed(QString, quint32)),
                     this, SLOT(onImageIndexed(QString, quint32)));
    connect(indexer, SIGNAL(finished()), this, SLOT(finished()));
    indexer->start();
}

void CommandBuildIndex::finished()
{
    QFile indexFile(mIndexFileName);
    indexFile.open(QIODevice::WriteOnly);
    indexFile.write(mFileData);
    indexFile.close();
    qDebug() << "Written file " << mIndexFileName;

    emit updateProgress(0);
    finish();

    mResourcesDirModel->setIndexBuilding(false);
}

void CommandBuildIndex::onImageIndexed(QString imageName, quint32 color)
{
    qDebug() << "Image " << imageName << " indexed with value " << color;
    QDataStream stream(&mFileData, QIODevice::Append);
    stream << imageName << color;
    emit updateProgress(imageConuter++);
}
