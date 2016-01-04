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

void ImageManipulatorBuilderTest::testBuilder()
{
    ImageManipulatorBuilder builder;
    builder.setFilename(TEST_RESOURCES_DIR + "/res1.png");

    mLibraryAdapter->returnValues("loadImage", { true });
    ImageManipulatorInt* manipulator = builder.build(*mLibraryAdapter);

    QVERIFY(manipulator);
    QCOMPARE(&manipulator->imageLibraryAdapter(), mLibraryAdapter);
}

void ImageManipulatorBuilderTest::testThrowsOnBadImage()
{
    ImageManipulatorBuilder builder;
    builder.setFilename(TEST_RESOURCES_DIR + "/res1.png");

    QVERIFY_EXCEPTION_THROWN(builder.build(*mLibraryAdapter), CannotLoadImage);
}

void ImageManipulatorBuilderTest::testThrowsOnBadPath()
{
    ImageManipulatorBuilder builder;
    builder.setFilename(TEST_RESOURCES_DIR + "/invalid_path.png");

    QVERIFY_EXCEPTION_THROWN(builder.build(*mLibraryAdapter), ImageDoNotExists);
}
