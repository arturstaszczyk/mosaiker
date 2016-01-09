#include "ImageModel.h"

#include <QDebug>

#include "Exceptions.h"

ImageModel::ImageModel(QObject *parent)
    : QObject(parent)
    , QQuickImageProvider(QQmlImageProviderBase::Image, 0)
{

}

void ImageModel::setOriginalImage(const QImage &image)
{
    mOriginalImage = image;
    emit imageUpdated();
}

QImage ImageModel::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    if(mOriginalImage.isNull())
        return mOriginalImage;

    qDebug() << "Image size:" << mOriginalImage.size();

    if(size)
        *size = requestedSize;

    return mOriginalImage;
}
