#include "PictureModel.h"

#include <QPainter>
#include <QColor>

#include "Exceptions.h"

PictureModel::PictureModel(QObject *parent)
    : QObject(parent)
    , QQuickImageProvider(QQmlImageProviderBase::Image, 0)
{

}

void PictureModel::setDisplayImage(const QImage &image)
{
    mDisplayImage = image;
    emit imageUpdated();
}

void PictureModel::setOverlayImage(const QImage &image)
{
    mOverlayImage = image;
    emit imageUpdated();
}

// Used by QtQuickEngine to display image in QML
// id - string passed from QML
// size - return size of image - QML element will be fixed to it
// requestedSize - passed from QML, sourceSize
QImage PictureModel::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);

    if(id == "displayImage" && mDisplayImage.isNull())
        return mDisplayImage;

    if(id == "overlayImage" && mOverlayImage.isNull())
        return mOverlayImage;

    if(id == "compositionImage" && mOverlayImage.isNull())
        return mDisplayImage;

    if(size)
    {
        *size = QSize(mDisplayImage.width(), mDisplayImage.height());

        if(!requestedSize.isEmpty())
        {
            mQmlSize = mDisplayImage.size().scaled(requestedSize.width(), requestedSize.height(),
                                                             Qt::KeepAspectRatio);
#ifdef TARGET_OS_MAC
            // mQmlSize is used to determine QML image size
            mQmlSize /= 2;
#endif

            *size = mQmlSize;
        }
    }

    emit sizeChanged();

    if(id == "displayImage")
        return mDisplayImage;

    if(id == "overlayImage")
        return mOverlayImage;

    if(id == "compositionImage")
    {
        mCompositionImage = QImage(mDisplayImage.size(), QImage::Format_ARGB32);
        QPainter painter(&mCompositionImage);

        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.drawImage(0, 0, mDisplayImage);
        painter.setOpacity(0.5);

        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawImage(0, 0, mOverlayImage);
        return mCompositionImage;
    }

    return mDisplayImage;
}
