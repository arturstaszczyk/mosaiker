#include "CommandCreateMosaic.h"

#include <QThread>
#include <QDebug>
#include <QPainter>

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
QList<QImage> quads;
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
    quads = mImageSlicer->slice(image, mSliceSize);

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
    imageName = mIndexLoader->closestFileNameByIndex(index);
    QImage toDraw(imageName);

    QImage& surface = mSecondaryImageModel->image();

    int wholeSlices = surface.width() / mSliceSize.width();
    int maxX = wholeSlices + (wholeSlices * mSliceSize.width() < surface.width() ? 1 : 0);
    int x, y;
    x = imageNo % maxX;
    y = imageNo / maxX;
    QPainter painter(&surface);
//    painter.drawImage(QRect(x * mSliceSize.width(), y * mSliceSize.height(),
//                            mSliceSize.width(), mSliceSize.height()), toDraw);

    painter.drawImage(QRect(x * mSliceSize.width(), y * mSliceSize.height(),
                            mSliceSize.width(), mSliceSize.height()),
                      quads[imageNo]);

    qDebug() << imageName << " " << imageNo << "/" << mImageSlicer->slices();
}
