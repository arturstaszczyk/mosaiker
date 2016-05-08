#include "CommandBuildIndex.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QColor>
#include <QDataStream>

#include "ImageIndexer.h"

static int imageConuter = 0;

CommandBuildIndex::CommandBuildIndex(IResourceFinder *finder, QFile& indexFile, QObject* parent)
        : Command(parent)
        , mResourceFinder(finder)
        , mIndexFile(indexFile)
{
    dynamic_cast<QObject*>(mResourceFinder)->setParent(this);
    mResourceFinder->addFilter({"*.jpg", "*.png", "*.jpeg"});


}

void CommandBuildIndex::execute()
{
    Q_ASSERT(mResourceFinder);

    mResourceFinder->find();
    auto list = mResourceFinder->resourcesList();
    emit resourcesCount(list.count());

    mIndexFile.open(QIODevice::WriteOnly);
    mFileData.clear();

    imageConuter = 0;

    QThread* indexer = new ImageIndexer(list);
    connect(indexer, SIGNAL(imageIndexed(QString, quint32)),
                     this, SLOT(onImageIndexed(QString, quint32)), Qt::AutoConnection);
    connect(indexer, SIGNAL(started()), this, SLOT(started()));
    connect(indexer, SIGNAL(finished()), this, SLOT(finished()));
    indexer->start();

//    mIndexFile.write(mFileData);
//    mIndexFile.close();
}

void CommandBuildIndex::started()
{
    qDebug() << "started";
}

void CommandBuildIndex::finished()
{
    qDebug() << "finished";
}

void CommandBuildIndex::onImageIndexed(QString imageName, quint32 color)
{
    qDebug() << "Image " << imageName << " indexed with value " << color;
    QDataStream stream(&mFileData, QIODevice::Append);
    stream << imageName << color;
    emit updateProgress(imageConuter++);
}
