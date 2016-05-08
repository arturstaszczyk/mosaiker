#include "ImageIndexer.h"

#include <QImage>
#include <QColor>
#include <QDebug>

ImageIndexer::ImageIndexer(QStringList imageList, QObject *parent)
    : //QThread(parent)
    mImageList(imageList)
{

}

void ImageIndexer::run()
{
    QString imageName;
    foreach(imageName, mImageList)
    {
//        QImage image(imageName);

        quint32 r = 0, g = 0, b = 0;

//        for(int x = 0; x < image.width(); ++x)
//        {
//            for(int y = 0; y < image.height(); ++y)
//            {
//                QRgb rgb = image.pixel(x, y);
//                r += qRed(rgb);
//                g += qGreen(rgb);
//                b += qBlue(rgb);
//            }
//        }

//        auto pixelCount = image.width() * image.height();
//        r /= pixelCount;
//        g /= pixelCount;
//        b /= pixelCount;
        qDebug() << "Indexed \n";
        emit imageIndexed(imageName, 0);//qRgb(r, g, b));
    }
}
