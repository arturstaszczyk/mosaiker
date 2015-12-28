#include "tst_ImageManipulatorTest.h"

#include <QObject>
#include <QtTest>

#include "ImageManipulator.h"
#include "mocks/ImageLibraryAdapterMock.h"

void ImageWrapperTest::init()
{
    mImageLibraryMockObj = new ImageLibraryAdapterMock();
}

void ImageWrapperTest::cleanup()
{
    delete mImageLibraryMockObj;
}

void ImageWrapperTest::testConstruction()
{
    ImageManipulator* manipulatorObj = new ImageManipulator(320, 240, mImageLibraryMockObj);

    QCOMPARE(manipulatorObj->width(), 320u);
    QCOMPARE(manipulatorObj->height(), 240u);
    QCOMPARE(manipulatorObj->imageLibraryAdapter(), mImageLibraryMockObj);

    QStringList expectedCalls { "genImage" };
    QCOMPARE(mImageLibraryMockObj->calls, expectedCalls);
    QCOMPARE(manipulatorObj->imageName(), mImageLibraryMockObj->genImage());
}

void ImageWrapperTest::testResize()
{
    ImageManipulator* manipulatorObj = new ImageManipulator(320, 240, mImageLibraryMockObj);
    manipulatorObj->resize(640, 480);

    QCOMPARE(manipulatorObj->width(), 640u);
    QCOMPARE(manipulatorObj->height(), 480u);

    QStringList calls {"genImage", "bindImage", "scale"};
    QCOMPARE(mImageLibraryMockObj->calls, calls);
}
