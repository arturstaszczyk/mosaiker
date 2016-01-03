#include "ImageManipulator.h"

#include <QFile>

#include "Exceptions.h"

const int ImageManipulator::IMAGE_CHANNELS_3 = 3;

ImageManipulator::ImageManipulator(const QSize& size, ImageLibraryAdapter& imageLibrary,
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

ImageManipulator::ImageManipulator(QString filename, ImageLibraryAdapter& imageLibrary,
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
        throw ImageDoNotExists();

    bool loaded = mImageLibraryObj.loadImage(filename);
    if(!loaded)
        throw CannotLoadImage();

    mImageSize.setWidth(mImageLibraryObj.getWidth());
    mImageSize.setHeight(mImageLibraryObj.getHeight());
}

ImageManipulator::ImageManipulator(const QSize& size, QByteArray data, ImageLibraryAdapter& imageLibrary,
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

QByteArray ImageManipulator::rawData()
{
    mImageLibraryObj.bindImage(mImageName);
    return mImageLibraryObj.getData();
}
