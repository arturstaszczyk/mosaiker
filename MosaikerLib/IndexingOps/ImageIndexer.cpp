#include "ImageIndexer.h"

#include <QDebug>
#include <HptIntegration.h>

#include "Exceptions.h"

ImageIndexer::ImageIndexer(QStringList imageList, QObject *parent)
    : QThread(parent)
    , mImageNamesList(imageList)
{

}

ImageIndexer::ImageIndexer(QList<QImage> imageList, QObject *parent)
    : QThread(parent)
    , mImagesList(imageList)
{

}

void ImageIndexer::run()
{
    PROFILE_SCOPE_START("ImageIndexer::start")
    if(!mImageNamesList.empty())
        runWithImageNames();
    else if(!mImagesList.empty())
        runWithImageList();
    else
        throw CannotIndexFiles();
    PROFILE_SCOPE_END()
}

void ImageIndexer::runWithImageNames()
{
    static QImage image;
    static QString imageName;

    for (int i = 0; i < mImageNamesList.count(); ++i)
    {
        PROFILE_SCOPE_START("ImageIndexer::runWithImageNames-loadImage")
        imageName = mImageNamesList[i];
        image = QImage(imageName);
        PROFILE_SCOPE_END()

        PROFILE_SCOPE_START("ImageIndexer::runWithImageNames-calculate")
        QRgb imageIndex = calculateImageIndex(convertToArgb(image));
        emit imageIndexed(i, imageName, imageIndex);
        PROFILE_SCOPE_END()
    }
}

void ImageIndexer::runWithImageList()
{
    for (int i = 0; i < mImagesList.count(); ++i)
    {
        PROFILE_SCOPE_START("ImageIndexer::runWithImageList-calculate")
        QRgb imageIndex = calculateImageIndex(convertToArgb(mImagesList[i]));
        emit imageIndexed(i, "", imageIndex);
        PROFILE_SCOPE_END()
    }
}

QImage ImageIndexer::convertToArgb(QImage image)
{
    if(image.format() != QImage::Format_ARGB32 && image.format() != QImage::Format_RGB32)
    {
        qWarning() << "Need to convert image to ARGB32 format";
        return image.convertToFormat(QImage::Format_ARGB32, Qt::AutoColor);
    }

    return image;
}

QRgb ImageIndexer::calculateImageIndex(QImage image)
{
    quint64 r, g, b, a;
    r = g = b = a = 0;

    for(int x = 0; x < image.width(); ++x)
    {
        for(int y = 0; y < image.height(); ++y)
        {
            QRgb rgb = image.pixel(x, y);
            r += qRed(rgb);
            g += qGreen(rgb);
            b += qBlue(rgb);
        }
    }

    auto pixelCount = image.width() * image.height();
    r /= pixelCount;
    g /= pixelCount;
    b /= pixelCount;

    return qRgb(r, g, b);
}
