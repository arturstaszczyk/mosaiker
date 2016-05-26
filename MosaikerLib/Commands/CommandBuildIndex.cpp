#include "CommandBuildIndex.h"

#include "HptIntegration.h"
#include "IndexingOps/ImageIndexer.h"

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
    PROFILE_SCOPE_START("CommandBuildIndex::execute")

    mResourceFinder->find();
    auto list = mResourceFinder->resourcesList();

    PROFILE_SCOPE_START("CommandBuildIndex::execute-indexing")
    QThread* indexer = new ImageIndexer(list, this);
    connect(indexer, SIGNAL(imageIndexed(quint32, QString, quint32)),
                     this, SLOT(onImageIndexed(quint32, QString, quint32)));
    connect(indexer, SIGNAL(finished()), this, SLOT(finished()));
    indexer->start();
    PROFILE_SCOPE_END()

    PROFILE_SCOPE_END()
}

void CommandBuildIndex::finished()
{
    PROFILE_SCOPE_START("CommandBuildIndex::finished")
    mIndexBuilder->save();
    finish();
    PROFILE_SCOPE_END()
}

void CommandBuildIndex::onImageIndexed(quint32 imageNo, QString imageName, quint32 color)
{
    mIndexBuilder->addIndexForFilename(color, imageName);

    float percentComplete = (float)(imageNo + 1) / (float)(mResourceFinder->resourcesList().count());
    emit commandProgress(100 * percentComplete);
}
