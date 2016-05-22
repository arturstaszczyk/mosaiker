#include "CommandCreateMosaic.h"

#include <QThread>
#include <QDebug>

#include "Exceptions.h"
#include "ImageIndexer.h"
#include "ImageCreator.h"

CommandCreateMosaic::CommandCreateMosaic(IImageSlicer* imageSlicer, IIndexLoader* indexLoader,
                                         PictureModel* primaryImage, PictureModel* secondaryImage,
                                         QObject* parent)
    : Command(COMMAND_NAME(CommandCreateMosaic), parent)
    , mImageSlicer(imageSlicer)
    , mIndexLoader(indexLoader)
    , mMainImageModel(primaryImage)
    , mSecondaryImageModel(secondaryImage)
    , mSliceSize(DEFAULT_SLICE_SIZE, DEFAULT_SLICE_SIZE)
{
    dynamic_cast<QObject*>(mImageSlicer)->setParent(this);
    dynamic_cast<QObject*>(mIndexLoader)->setParent(this);
}

void CommandCreateMosaic::setSliceSize(quint32 sizeInPixels)
{
    mSliceSize.setWidth(sizeInPixels);
    mSliceSize.setHeight(sizeInPixels);
}

void CommandCreateMosaic::setSliceSize(QSize size)
{
    mSliceSize = size;
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

    QImage surfaceImage = QImage(mMainImageModel->image().size(), QImage::Format_RGB32);
    mSecondaryImageModel->setImage(surfaceImage);

    auto image = mMainImageModel->image();
    auto quads = mImageSlicer->slice(image, mSliceSize);

    QThread* indexer = new ImageIndexer(quads, this);
    connect(indexer, SIGNAL(imageIndexed(quint32, QString, quint32)),
                     this, SLOT(onImageIndexed(quint32, QString, quint32)));
    connect(indexer, SIGNAL(finished()), this, SLOT(indexingFinished()));

    indexer->start();

}

void CommandCreateMosaic::onImageIndexed(quint32 imageNo, QString imageName, quint32 index)
{
    Q_UNUSED(imageNo);
    imageName = mIndexLoader->closestFileNameByIndex(index);
    mImageNames.append(imageName);

    qDebug() << "Images " << imageNo + 1 << "/" << mImageSlicer->slices() << " indexed";
}

void CommandCreateMosaic::indexingFinished()
{
    ImageCreator* imageCreator = new ImageCreator(mMainImageModel->image().size(), mSliceSize,
                                                  mImageNames, this);
    connect(imageCreator, SIGNAL(imageCreated(QImage)), this, SLOT(imageCreated(QImage)));
    connect(imageCreator, SIGNAL(finished()), this, SLOT(finishCommand()));

    imageCreator->start();
}

void CommandCreateMosaic::imageCreated(QImage image)
{
    mSecondaryImageModel->setImage(image);
}

void CommandCreateMosaic::finishCommand()
{
    finish();
}
