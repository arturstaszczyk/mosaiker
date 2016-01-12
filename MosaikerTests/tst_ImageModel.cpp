#include "tst_ImageModel.h"

#include <QtTest>
#include <QImage>
#include <QSignalSpy>

#include <Models/ImageModel.h>

void ImageModelTest::testImageModelResized()
{
    QImage mockImage(32, 32, QImage::Format_ARGB32);

    ImageModel imageModel;
    QSignalSpy spy(&imageModel, SIGNAL(imageUpdated()));

    imageModel.setOriginalImage(mockImage);

    QCOMPARE(spy.count(), 1);

    QSize size;
    QImage image = imageModel.requestImage("original", &size, QSize(64, 64));

    QCOMPARE(size.width(), 64);
    QCOMPARE(size.height(), 64);

    QCOMPARE(image.width(), 64);
    QCOMPARE(image.height(), 64);
}

void ImageModelTest::testImageModelOriginal()
{
    QImage mockImage(32, 32, QImage::Format_ARGB32);

    ImageModel imageModel;
    QSignalSpy spy(&imageModel, SIGNAL(imageUpdated()));
    imageModel.setOriginalImage(mockImage);

    QCOMPARE(spy.count(), 1);

    QSize size;
    QImage image = imageModel.requestImage("original", &size, QSize());

    QCOMPARE(size.width(), 32);
    QCOMPARE(size.height(), 32);

    QCOMPARE(image.width(), 32);
    QCOMPARE(image.height(), 32);
}
