#include "tst_ImageManipulatorTest.h"

#include <QObject>
#include <QtTest>

#include "Exceptions.h"
#include "ImageManipulator.h"
#include "mocks/ImageLibraryAdapterMock.h"

#define TEST_RESOURCES_DIR QString("./TestResources")

void ImageWrapperTest::init()
{
    mImageLibraryMockObj = new ImageLibraryAdapterMock();
}

void ImageWrapperTest::cleanup()
{
    delete mImageLibraryMockObj;
}

void ImageWrapperTest::testEmptyConstruction()
{
    ImageManipulator* manipulatorObj = new ImageManipulator(320, 240, mImageLibraryMockObj);

    QCOMPARE(manipulatorObj->width(), 320u);
    QCOMPARE(manipulatorObj->height(), 240u);
    QCOMPARE(manipulatorObj->imageLibraryAdapter(), mImageLibraryMockObj);

    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("genImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("bindImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("texImage"));

    QCOMPARE(mImageLibraryMockObj->calls().count(), 3);
    QCOMPARE(manipulatorObj->imageName(), mImageLibraryMockObj->genImage());
}

void ImageWrapperTest::testFileConstruction()
{
    mImageLibraryMockObj->returnValues("loadImage", { true });
    ImageManipulator* manipulatorObj = new ImageManipulator(TEST_RESOURCES_DIR + "/res1.png", mImageLibraryMockObj);
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("genImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("bindImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("loadImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("getWidth"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("getHeight"));

    QCOMPARE(manipulatorObj->width() ,mImageLibraryMockObj->getWidth());
    QCOMPARE(manipulatorObj->height() ,mImageLibraryMockObj->getHeight());
}

void ImageWrapperTest::testInvalidFilePathConstruction()
{
    QVERIFY_EXCEPTION_THROWN(new ImageManipulator("filename.png", mImageLibraryMockObj), ImageDoNotExists);
}

void ImageWrapperTest::testImageLoadFailed()
{
    mImageLibraryMockObj->returnValues("loadImage", { false });
    QVERIFY_EXCEPTION_THROWN(ImageManipulator(TEST_RESOURCES_DIR + "/res1.png", mImageLibraryMockObj),
                             CannotLoadImage);
}

void ImageWrapperTest::testResize()
{
    ImageManipulator* manipulatorObj = new ImageManipulator(320, 240, mImageLibraryMockObj);

    mImageLibraryMockObj->reset();
    manipulatorObj->resize(640, 480);

    QCOMPARE(manipulatorObj->width(), 640u);
    QCOMPARE(manipulatorObj->height(), 480u);

    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("bindImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("scale"));

    QCOMPARE(mImageLibraryMockObj->callArgs("bindImage").count(), 1);
    QCOMPARE(mImageLibraryMockObj->callArgs("scale").count(), 2);
}
