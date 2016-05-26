#include "ImageIndexer.h"

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
        QRgb imageIndex = calculateImageIndex(image);
        emit imageIndexed(i, imageName, imageIndex);
        PROFILE_SCOPE_END()
    }
}

void ImageIndexer::runWithImageList()
{
    for (int i = 0; i < mImagesList.count(); ++i)
    {
        PROFILE_SCOPE_START("ImageIndexer::runWithImageList-calculate")
        QRgb imageIndex = calculateImageIndex(mImagesList[i]);
        emit imageIndexed(i, "", imageIndex);
        PROFILE_SCOPE_END()
    }
}

QRgb ImageIndexer::calculateImageIndex(QImage image)
{
    quint32 r = 0, g = 0, b = 0;

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
