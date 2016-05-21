#include "MainImageModel.h"

#include "Exceptions.h"

PictureModel::PictureModel(QObject *parent)
    : QObject(parent)
    , QQuickImageProvider(QQmlImageProviderBase::Image, 0)
{

}

void PictureModel::setImage(const QImage &image)
{
    mOriginalImage = image;
    emit imageUpdated();
}

// Used by QtQuickEngine to display image in QML
// id - string passed from QML
// size - return size of image - QML element will be fixed to it
// requestedSize - passed from QML, sourceSize
QImage PictureModel::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);

    if(mOriginalImage.isNull())
        return mOriginalImage;

    if(size)
    {
        *size = QSize(mOriginalImage.width(), mOriginalImage.height());

        if(!requestedSize.isEmpty())
        {
            mDesiredSize = mOriginalImage.size().scaled(requestedSize.width(), requestedSize.height(),
                                                             Qt::KeepAspectRatio);
#ifdef TARGET_OS_MAC
            // mDesiredSize is used to determine QML image size
            mDesiredSize /= 2;
#endif

            *size = mDesiredSize;
        }
    }

    emit sizeChanged();
    return mOriginalImage;
}
