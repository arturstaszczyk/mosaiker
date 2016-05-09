#include "MainImageModel.h"

#include <QDebug>

#include "Exceptions.h"

MainImageModel::MainImageModel(QObject *parent)
    : QObject(parent)
    , QQuickImageProvider(QQmlImageProviderBase::Image, 0)
{

}

void MainImageModel::setMainImage(const QImage &image)
{
    mOriginalImage = image;
    emit imageUpdated();
}

QImage MainImageModel::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
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
        }
    }

    emit sizeChanged();
    return mOriginalImage;
}
