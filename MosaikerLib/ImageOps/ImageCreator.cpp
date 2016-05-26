#include "ImageCreator.h"

#include <HptIntegration.h>

#include <QDebug>
#include <QPainter>

ImageCreator::ImageCreator(QSize targetImageSize, QSize sliceSize, QStringList imageNames, QObject* parent)
    : QThread(parent)
    , mImageNames(imageNames)
    , mImageSize(targetImageSize)
    , mSliceSize(sliceSize)
{

}

void ImageCreator::run()
{
    PROFILE_SCOPE_START("ImageCreator::run")
    QImage surface(mImageSize, QImage::Format_ARGB32);
    int wholeSlices = surface.width() / mSliceSize.width();
    int maxX = wholeSlices + (wholeSlices * mSliceSize.width() < surface.width() ? 1 : 0);

    for(int imageNo = 0; imageNo < mImageNames.count(); ++imageNo)
    {
        PROFILE_SCOPE_START("ImageCreator::run-forLoop")
        int x, y;
        x = imageNo % maxX;
        y = imageNo / maxX;

        QImage toDraw(mImageNames[imageNo]);
        QPainter painter(&surface);

        painter.drawImage(QRect(x * mSliceSize.width(), y * mSliceSize.height(),
                                mSliceSize.width(), mSliceSize.height()), toDraw);

        qDebug() << mImageNames[imageNo] << " " << imageNo << "/" << mImageNames.count();

        emit sliceDrawn(imageNo);
        PROFILE_SCOPE_END()
    }

    emit imageCreated(surface);
    PROFILE_SCOPE_END()
}
