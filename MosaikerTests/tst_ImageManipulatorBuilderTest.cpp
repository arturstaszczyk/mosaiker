#include "tst_ImageManipulatorBuilderTest.h"

#include <QtTest>

#include "Exceptions.h"
#include "Interfaces/ImageManipulatorInt.h"
#include "ImageManipulatorBuilder.h"

void ImageManipulatorBuilderTest::init()
{
    mLibraryAdapter = new ImageLibraryAdapterMock();
}

void ImageManipulatorBuilderTest::cleanup()
{
    delete mLibraryAdapter;
}

void ImageManipulatorBuilderTest::testBuilderFromFile()
{
    ImageManipulatorBuilder builder(*mLibraryAdapter);
    builder.setFilename(TEST_RESOURCES_DIR + "/res1.png");

    mLibraryAdapter->returnValues("loadImage", { true });
    ImageManipulatorInt* manipulator = builder.build();

    QVERIFY(manipulator);
    QCOMPARE(&manipulator->imageLibraryAdapter(), mLibraryAdapter);
}

void ImageManipulatorBuilderTest::testThrowsOnBadImage()
{
    ImageManipulatorBuilder builder(*mLibraryAdapter);
    builder.setFilename(TEST_RESOURCES_DIR + "/res1.png");

    QVERIFY_EXCEPTION_THROWN(builder.build(), CannotLoadImage);
}

void ImageManipulatorBuilderTest::testThrowsOnBadPath()
{
    ImageManipulatorBuilder builder(*mLibraryAdapter);
    builder.setFilename(TEST_RESOURCES_DIR + "/invalid_path.png");

    QVERIFY_EXCEPTION_THROWN(builder.build(), ImageDoNotExists);
}

void ImageManipulatorBuilderTest::testBuilderEmpty()
{
    ImageManipulatorBuilder builder(*mLibraryAdapter);
    builder.setSize(QSize(32, 32));

    ImageManipulatorInt* manipulator = builder.build();

    QVERIFY(manipulator);
    QCOMPARE(&manipulator->imageLibraryAdapter(), mLibraryAdapter);
    QCOMPARE(manipulator->width(), 32);
    QCOMPARE(manipulator->height(), 32);
}

void ImageManipulatorBuilderTest::testBuildFromBytes()
{
    ImageManipulatorBuilder builder(*mLibraryAdapter);
    QByteArray bytes(32 * 32 * 3, '\0');
    builder.setBytes(bytes);
    builder.setSize(QSize(32, 32));

    ImageManipulatorInt* manipulator = builder.build();

    QVERIFY(manipulator);
    QCOMPARE(&manipulator->imageLibraryAdapter(), mLibraryAdapter);
    QCOMPARE(manipulator->width(), 32);
    QCOMPARE(manipulator->height(), 32);
}

void ImageManipulatorBuilderTest::testThrowsOnNotEnoughData()
{
    ImageManipulatorBuilder builder(*mLibraryAdapter);
    QByteArray bytes(32 * 32 * 3, '\0');
    builder.setBytes(bytes);

    QVERIFY_EXCEPTION_THROWN(builder.build(), CannotCreateImage);
}
