#include "CommandCreateMosaic.h"

#include <QThread>
#include <QDebug>

#include <HptIntegration.h>

#include "Exceptions.h"
#include "ImageOps/ImageCreator.h"
#include "IndexingOps/ImageIndexer.h"

CommandCreateMosaic::CommandCreateMosaic(IImageSlicer* imageSlicer, IIndexLoader* indexLoader,
                                         PictureModel* primaryImage, QObject* parent)
    : Command(COMMAND_NAME(CommandCreateMosaic), parent)
    , mImageSlicer(imageSlicer)
    , mIndexLoader(indexLoader)
    , mPictureModel(primaryImage)
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
    PROFILE_SCOPE_START("CommandCreateMosaic::execute-loadIndex")
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
    PROFILE_SCOPE_END()

    PROFILE_SCOPE_START("CommandCreateMosaic::execute-sliceImage")
    auto image = mPictureModel->displayImage();
    auto slices = mImageSlicer->slice(image, mSliceSize);

    QThread* indexer = new ImageIndexer(slices, this);
    connect(indexer, SIGNAL(imageIndexed(quint32, QString, quint32)),
                     this, SLOT(onSliceIndexed(quint32, QString, quint32)));
    connect(indexer, SIGNAL(finished()), this, SLOT(onIndexingFinished()));

    indexer->start();

    PROFILE_SCOPE_END()
}

void CommandCreateMosaic::onSliceIndexed(quint32 imageNo, QString imageName, quint32 index)
{
    Q_UNUSED(imageNo);
    imageName = mIndexLoader->closestFileNameByIndex(index);
    mImageNames.append(imageName);

    qDebug() << "Images " << imageNo + 1 << "/" << mImageSlicer->slices() << " indexed";
}

void CommandCreateMosaic::onIndexingFinished()
{
    ImageCreator* imageCreator = new ImageCreator(mPictureModel->displayImage().size(), mSliceSize,
                                                  mImageNames, this);
    connect(imageCreator, SIGNAL(sliceDrawn(quint32)), this, SLOT(onImageCreatorDrawn(quint32)));
    connect(imageCreator, SIGNAL(imageCreated(QImage)), this, SLOT(onImageCreated(QImage)));
    connect(imageCreator, SIGNAL(finished()), this, SLOT(onImageCreatorFinished()));

    imageCreator->start();
}

void CommandCreateMosaic::onImageCreatorDrawn(quint32 sliceNo)
{
    float percentDone = (float)(sliceNo + 1) / (float)mImageSlicer->slices();
    emit commandProgress(percentDone * 100);
}

void CommandCreateMosaic::onImageCreated(QImage image)
{
    mPictureModel->setOverlayImage(image);
}

void CommandCreateMosaic::onImageCreatorFinished()
{
    finish();
}
