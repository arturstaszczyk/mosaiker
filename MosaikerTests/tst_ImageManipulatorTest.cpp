#include "tst_ImageManipulatorTest.h"

#include <QObject>
#include <QtTest>

#include "tst_Common.h"
#include "Exceptions.h"
#include "ImageManipulator.h"
#include "mocks/ImageLibraryAdapterMock.h"

void ImageManipulatorTest::init()
{
    mImageLibraryMockObj = new ImageLibraryAdapterMock();
}

void ImageManipulatorTest::cleanup()
{
    delete mImageLibraryMockObj;
}

void ImageManipulatorTest::testEmptyConstruction()
{
    quint32 expectedImageName = 42;
    QSize expectedSize(320, 240);
    mImageLibraryMockObj->returnValues("genImage", { expectedImageName });

    ImageManipulator manipulatorObj(expectedSize, *mImageLibraryMockObj);

    QCOMPARE(manipulatorObj.width(), expectedSize.width());
    QCOMPARE(manipulatorObj.height(), expectedSize.height());
    QCOMPARE(&manipulatorObj.imageLibraryAdapter(), mImageLibraryMockObj);

    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("genImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("bindImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("texImage24RGB"));

    QCOMPARE(mImageLibraryMockObj->calls().count(), 3);
    QCOMPARE(manipulatorObj.imageName(), expectedImageName);
}

void ImageManipulatorTest::testFileConstruction()
{
    mImageLibraryMockObj->returnValues("loadImage", { true });
    mImageLibraryMockObj->returnValues("getWidth", { 320, 320 });
    mImageLibraryMockObj->returnValues("getHeight", { 240, 240 });

    ImageManipulator manipulatorObj(TEST_RESOURCES_DIR + "/res1.png", *mImageLibraryMockObj);

    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("genImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("bindImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("loadImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("getWidth"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("getHeight"));

    QCOMPARE(manipulatorObj.width() ,mImageLibraryMockObj->getWidth());
    QCOMPARE(manipulatorObj.height() ,mImageLibraryMockObj->getHeight());
}

void ImageManipulatorTest::testInvalidFilePathConstruction()
{
    QVERIFY_EXCEPTION_THROWN(new ImageManipulator("filename.png", *mImageLibraryMockObj), ResourceDoNotExists);
}

void ImageManipulatorTest::testDataConstruction()
{
    QSize expectedSize(320, 240);

    QByteArray bytes(expectedSize.width() * expectedSize.height() * ImageManipulator::IMAGE_CHANNELS_3, '\0');
    ImageManipulator manipulatorObj(expectedSize, bytes, *mImageLibraryMockObj);

    QVERIFY(manipulatorObj.width() == expectedSize.width());
    QVERIFY(manipulatorObj.height() == expectedSize.height());

    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("genImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("bindImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("texImage24RGB"));

    auto args = mImageLibraryMockObj->callArgs("texImage24RGB");
    QCOMPARE(args.count(), 3);
    QVERIFY(args[0].toInt() == expectedSize.width());
    QVERIFY(args[1].toInt() == expectedSize.height());
}

void ImageManipulatorTest::testImageLoadFailed()
{
    mImageLibraryMockObj->returnValues("loadImage", { false });
    QVERIFY_EXCEPTION_THROWN(ImageManipulator(TEST_RESOURCES_DIR + "/res1.png", *mImageLibraryMockObj),
                             CannotLoadImage);
}

void ImageManipulatorTest::testResize()
{
    QSize initialSize(320, 240);
    QSize expectedSize(640, 480);

    ImageManipulator manipulatorObj(initialSize, *mImageLibraryMockObj);

    mImageLibraryMockObj->reset();
    manipulatorObj.resize(expectedSize);

    QCOMPARE(manipulatorObj.width(), expectedSize.width());
    QCOMPARE(manipulatorObj.height(), expectedSize.height());

    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("bindImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("scale"));

    QCOMPARE(mImageLibraryMockObj->callArgs("bindImage").count(), 1);
    QCOMPARE(mImageLibraryMockObj->callArgs("scale").count(), 2);

    QCOMPARE(mImageLibraryMockObj->callArgs("scale")[0].toInt(), expectedSize.width());
    QCOMPARE(mImageLibraryMockObj->callArgs("scale")[1].toInt(), expectedSize.height());
}

void ImageManipulatorTest::testDeleteObject()
{
    auto manipulator = new ImageManipulator(QSize(10, 10), *mImageLibraryMockObj);
    manipulator->resize(QSize(32, 32));
    delete manipulator;

    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("deleteImage"));
}

void ImageManipulatorTest::testCreateSubImage()
{
    mImageLibraryMockObj->returnValues("genImage", { 1, 2 });
    ImageManipulator manipulator(QSize(32, 32), *mImageLibraryMockObj);

    mImageLibraryMockObj->reset();
    std::auto_ptr<ImageManipulator> subManipulator(manipulator.imageManipulatorForSubimage(QRect(0, 0, 16, 16)));
    QVERIFY(mImageLibraryMockObj->hasCalls("bindImage", 2));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("copyPixels24RGB"));

    QCOMPARE(subManipulator->width(), 16);
    QCOMPARE(subManipulator->height(), 16);
    QCOMPARE(&subManipulator->imageLibraryAdapter(), mImageLibraryMockObj);

    QVERIFY(subManipulator->imageName() != manipulator.imageName());
}

void ImageManipulatorTest::testGetData()
{
    QByteArray expected = QByteArray(32 * 32 * ImageManipulator::IMAGE_CHANNELS_3, '\0');

    ImageManipulator manipulator(QSize(32, 32), *mImageLibraryMockObj);
    mImageLibraryMockObj->reset();

    mImageLibraryMockObj->returnValues("getData", { expected });
    QCOMPARE(manipulator.rawData().size(), expected.size());
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("bindImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("getData"));
}

void ImageManipulatorTest::testSaveImage()
{
    ImageManipulator manipulator(QSize(32, 32), *mImageLibraryMockObj);
    mImageLibraryMockObj->reset();

    manipulator.saveAsPng("test.png");
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("bindImage"));
    QVERIFY(mImageLibraryMockObj->hasExactlyOneCall("save"));

    QCOMPARE(mImageLibraryMockObj->callArgs("save")[0].toString(), QString("test.png"));
}

void ImageManipulatorTest::testToQImage()
{
    ImageManipulator manipulator(QSize(32, 32), *mImageLibraryMockObj);
    QImage image = manipulator.toQImage();

    QCOMPARE(image.width(), 32);
    QCOMPARE(image.height(), 32);
}
