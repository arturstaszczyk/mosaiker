#include "CommandCreateMosaic.h"

#include <QThread>
#include <QDebug>

#include "Exceptions.h"
#include "ImageIndexer.h"

CommandCreateMosaic::CommandCreateMosaic(IImageSlicer* imageSlicer, IIndexLoader* indexLoader,
                                         PictureModel* primaryImage, PictureModel* secondaryImage,
                                         QObject* parent)
    : Command(COMMAND_NAME(CommandCreateMosaic), parent)
    , mImageSlicer(imageSlicer)
    , mIndexLoader(indexLoader)
    , mMainImageModel(primaryImage)
    , mSecondaryImageModel(secondaryImage)
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
    connect(indexer, SIGNAL(imageIndexed(quint32, QString, quint32)),
                     this, SLOT(onImageIndexed(quint32, QString, quint32)));
    connect(indexer, SIGNAL(finished()), this, SLOT(finished()));

    indexer->start();
}

void CommandCreateMosaic::finished()
{
    finish();
}

void CommandCreateMosaic::onImageIndexed(quint32 imageNo, QString imageName, quint32 index)
{
    Q_UNUSED(imageNo);
    imageName = mIndexLoader->closestFileNameByIndex(index);
    qDebug() << imageName;
}
