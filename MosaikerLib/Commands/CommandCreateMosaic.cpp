#include "CommandCreateMosaic.h"

#include <QThread>
#include <QDebug>

#include "Exceptions.h"
#include "ImageIndexer.h"

CommandCreateMosaic::CommandCreateMosaic(IImageSlicer* imageSlicer, IIndexLoader* indexLoader,
                                         MainImageModel* imageModel, QObject* parent)
    : Command(COMMAND_NAME(CommandCreateMosaic), parent)
    , mImageSlicer(imageSlicer)
    , mIndexLoader(indexLoader)
    , mMainImageModel(imageModel)
{
    dynamic_cast<QObject*>(mImageSlicer)->setParent(this);
    dynamic_cast<QObject*>(mIndexLoader)->setParent(this);
}

void CommandCreateMosaic::execute()
{
    try
    {
        mIndexLoader->loadIndex();
    }
    catch(PathDoNotExists ex)
    {
        qDebug() << "PathDoNotExists" << ex.what();
        finish();
        return;
    }

    auto image = mMainImageModel->image();
    auto quads = mImageSlicer->slice(image, QSize(64, 64));

    QThread* indexer = new ImageIndexer(quads, this);
    connect(indexer, SIGNAL(imageIndexed(QString, quint32)),
                     this, SLOT(onImageIndexed(QString, quint32)));
    connect(indexer, SIGNAL(finished()), this, SLOT(finished()));

    indexer->start();
}

void CommandCreateMosaic::finished()
{
    finish();
}

void CommandCreateMosaic::onImageIndexed(QString name, quint32 color)
{
    name = mIndexLoader->closestFileNameByIndex(color);
    qDebug() << name;
}
