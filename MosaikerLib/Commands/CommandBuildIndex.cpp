#include "CommandBuildIndex.h"

#include "ImageIndexer.h"

CommandBuildIndex::CommandBuildIndex(IResourceFinder* resourcesFinder, IIndexBuilder* indexBuilder, QObject* parent)
        : Command(COMMAND_NAME(CommandBuildIndex), parent)
        , mResourceFinder(resourcesFinder)
        , mIndexBuilder(indexBuilder)
{
    dynamic_cast<QObject*>(indexBuilder)->setParent(this);
    dynamic_cast<QObject*>(mResourceFinder)->setParent(this);
}

void CommandBuildIndex::execute()
{
    mResourceFinder->find();
    auto list = mResourceFinder->resourcesList();

    QThread* indexer = new ImageIndexer(list, this);
    connect(indexer, SIGNAL(imageIndexed(quint32, QString, quint32)),
                     this, SLOT(onImageIndexed(quint32, QString, quint32)));
    connect(indexer, SIGNAL(finished()), this, SLOT(finished()));
    indexer->start();
}

void CommandBuildIndex::finished()
{
    mIndexBuilder->save();
    finish();
}

void CommandBuildIndex::onImageIndexed(quint32 imageNo, QString imageName, quint32 color)
{
    mIndexBuilder->addIndexForFilename(color, imageName);

    float percentComplete = (float)(imageNo + 1) / (float)(mResourceFinder->resourcesList().count());
    emit commandProgress(100 * percentComplete);
}
