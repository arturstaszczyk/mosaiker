#include "CommandBuildIndex.h"

#include "ImageIndexer.h"

CommandBuildIndex::CommandBuildIndex(IResourceFinder* resourcesFinder, IIndexBuilder* indexBuilder, QObject* parent)
        : Command(COMMAND_NAME(CommandBuildIndex), parent)
        , mResourceFinder(resourcesFinder)
        , mIndexBuilder(indexBuilder)
{
    dynamic_cast<QObject*>(indexBuilder)->setParent(this);
    dynamic_cast<QObject*>(mResourceFinder)->setParent(this);

    mResourceFinder->addFilter({"*.jpg", "*.png", "*.jpeg"});
}

void CommandBuildIndex::execute()
{
    mResourceFinder->find();
    auto list = mResourceFinder->resourcesList();
    emit resourcesCount(list.count());

    QThread* indexer = new ImageIndexer(list, this);
    connect(indexer, SIGNAL(imageIndexed(quint32, QString, quint32)),
                     this, SLOT(onImageIndexed(quint32, QString, quint32)));
    connect(indexer, SIGNAL(finished()), this, SLOT(finished()));
    indexer->start();
}

void CommandBuildIndex::finished()
{
    mIndexBuilder->save();

    emit updateProgress(0);
    finish();
}

void CommandBuildIndex::onImageIndexed(quint32 imageNo, QString imageName, quint32 color)
{
    mIndexBuilder->addIndexForFilename(color, imageName);

    emit updateProgress(imageNo + 1);
}
