#include "ImageManipulator.h"

#include <QFile>
#include <QImage>

#include "Exceptions.h"

const int ImageManipulator::IMAGE_CHANNELS_3 = 3;

void qImageCleanupHandler(void* data)
{
    delete [] static_cast<const char*>(data);
}

ImageManipulator::ImageManipulator(const QSize& size, IImageLibraryAdapter& imageLibrary,
                                   QObject *parent)
    : QObject(parent)
    , mImageLibraryObj(imageLibrary)
    , mImageName(0)
    , mImageSize(size)
{
    mImageName = mImageLibraryObj.genImage();
    mImageLibraryObj.bindImage(mImageName);

    QByteArray imageBytes(mImageSize.width() * mImageSize.height() * IMAGE_CHANNELS_3, '\0');
    mImageLibraryObj.texImage24RGB(mImageSize.width(), mImageSize.height(), imageBytes.data()); // create black image
}

ImageManipulator::ImageManipulator(QString filename, IImageLibraryAdapter& imageLibrary,
                                   QObject* parent)
    : QObject(parent)
    , mImageLibraryObj(imageLibrary)
    , mImageName(0)
    , mImageSize(0, 0)
{
    mImageName = mImageLibraryObj.genImage();
    mImageLibraryObj.bindImage(mImageName);

    QFile imageFile(filename);
    if(!imageFile.exists())
        throw ResourceDoNotExists();

    bool loaded = mImageLibraryObj.loadImage(filename);
    if(!loaded)
        throw CannotLoadImage();

    mImageSize.setWidth(mImageLibraryObj.getWidth());
    mImageSize.setHeight(mImageLibraryObj.getHeight());
}

ImageManipulator::ImageManipulator(const QSize& size, QByteArray data, IImageLibraryAdapter& imageLibrary,
                          QObject* parent)
    : QObject(parent)
    , mImageLibraryObj(imageLibrary)
    , mImageName(0)
    , mImageSize(size)
{
    mImageName = mImageLibraryObj.genImage();
    mImageLibraryObj.bindImage(mImageName);

    mImageLibraryObj.texImage24RGB(mImageSize.width(), mImageSize.height(), data.data()); // create image with provided data
}

ImageManipulator::~ImageManipulator()
{
    mImageLibraryObj.deleteImage(mImageName);
}

void ImageManipulator::resize(const QSize& newSize)
{
    mImageLibraryObj.bindImage(0);
    mImageLibraryObj.scale(newSize.width(), newSize.height());

    mImageSize = newSize;
}

ImageManipulator* ImageManipulator::imageManipulatorForSubimage(const QRect &imageRect)
{
    QSize newSize(imageRect.width(), imageRect.height());

    mImageLibraryObj.bindImage(mImageName);

    QByteArray data(imageRect.width() * imageRect.height() * ImageManipulator::IMAGE_CHANNELS_3, '\0');
    mImageLibraryObj.copyPixels24RGB(imageRect.x(), imageRect.y(), newSize.width(), newSize.height(), data.data());

    return new ImageManipulator(newSize, data, mImageLibraryObj);
}

void ImageManipulator::saveAsPng(QString fileName)
{
    mImageLibraryObj.bindImage(mImageName);
    mImageLibraryObj.save(fileName);
}

QImage ImageManipulator::toQImage() const
{
    quint32 dataLen = width() * height() * ImageManipulator::IMAGE_CHANNELS_3;
    char* imageData = new char[dataLen];

    mImageLibraryObj.bindImage(mImageName);
    mImageLibraryObj.copyPixels24RGB(0, 0, width(), height(), imageData);

    return QImage(reinterpret_cast<uchar*>(imageData), width(), height(),
                             QImage::Format_RGB888, qImageCleanupHandler,
                             static_cast<void*>(imageData));

}

QByteArray ImageManipulator::rawData()
{
    mImageLibraryObj.bindImage(mImageName);
    return mImageLibraryObj.getData();
}
