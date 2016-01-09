#include "ImageModel.h"

ImageModel::ImageModel(QObject *parent)
    : QObject(parent)
    , QQuickImageProvider(QQmlImageProviderBase::Image, 0)
{

}

void ImageModel::setOriginalImage(const QImage &image)
{

}

QImage ImageModel::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return QImage();
}
