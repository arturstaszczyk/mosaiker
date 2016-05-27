#include "PictureModel.h"

#include <QPainter>
#include <QColor>
#include <cmath>

#include "Exceptions.h"

PictureModel::PictureModel(QObject *parent)
    : QObject(parent)
    , QQuickImageProvider(QQmlImageProviderBase::Image, 0)
    , mImageOpacity(0.5)
{

}

void PictureModel::setDisplayImage(const QImage &image)
{
    mDisplayImage = image;
    emit composedImageUpdated();
}

void PictureModel::setOverlayImage(const QImage &image)
{
    mOverlayImage = image;
    emit composedImageUpdated();
}

void PictureModel::setOpacity(qreal opacity)
{
    if(std::abs(mImageOpacity - opacity) > 0.0001)
    {
        mImageOpacity = opacity;
        emit opacityChanged(mImageOpacity);
        emit composedImageUpdated();
    }
}

// Used by QtQuickEngine to display image in QML
// id - string passed from QML
// size - return size of image - QML element will be fixed to it
// requestedSize - passed from QML, sourceSize
QImage PictureModel::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);

    calculateSize(size, requestedSize);

    if(id == "displayImage")
        return mDisplayImage;

    if(id == "overlayImage")
        return mOverlayImage;

    if(id == "compositionImage")
    {
        mergeDisplayWithOverlayImages();
        return mCompositionImage;
    }

    return mDisplayImage;
}

void PictureModel::calculateSize(QSize *size, const QSize& requestedSize)
{
    if(!requestedSize.isEmpty())
    {
        mQmlSize = mDisplayImage.size().scaled(requestedSize.width(), requestedSize.height(),
                                                         Qt::KeepAspectRatio);
#ifdef TARGET_OS_MAC
        // mQmlSize is used to determine QML image size
        mQmlSize /= 2;
#endif
    }
    else
    {
        mQmlSize = QSize(mDisplayImage.width(), mDisplayImage.height());
    }

    if(size && !mDisplayImage.isNull())
        *size = mQmlSize;

    emit sizeChanged();
}

void PictureModel::mergeDisplayWithOverlayImages()
{
    mCompositionImage = QImage(mDisplayImage.size(), QImage::Format_ARGB32);
    QPainter painter(&mCompositionImage);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawImage(0, 0, mDisplayImage);
    painter.setOpacity(mImageOpacity);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, mOverlayImage);
}
