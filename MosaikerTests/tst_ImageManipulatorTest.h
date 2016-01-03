#ifndef TST_IMAGEWRAPPERTEST_H
#define TST_IMAGEWRAPPERTEST_H

#include <QObject>
#include "mocks/ImageLibraryAdapterMock.h"

class ImageManipulatorTest : public QObject
{
    Q_OBJECT

public:
    ImageManipulatorTest()
    {}

private Q_SLOTS:
    void init();
    void cleanup();

    void testEmptyConstruction();
    void testFileConstruction();
    void testInvalidFilePathConstruction();
    void testDataConstruction();
    void testImageLoadFailed();
    void testResize();
    void testDeleteObject();
    void testCreateSubImage();
    void testGetData();
    void testSaveImage();

private:
    ImageLibraryAdapterMock* mImageLibraryMockObj;
};

#endif // TST_IMAGEWRAPPERTEST_H

