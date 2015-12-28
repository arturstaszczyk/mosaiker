#ifndef TST_IMAGEWRAPPERTEST_H
#define TST_IMAGEWRAPPERTEST_H

#include <QObject>
#include "mocks/ImageLibraryAdapterMock.h"

class ImageWrapperTest : public QObject
{
    Q_OBJECT

public:
    ImageWrapperTest()
    {}

private Q_SLOTS:
    void init();
    void cleanup();

    void testConstruction();
    void testResize();

private:
    ImageLibraryAdapterMock* mImageLibraryMockObj;
};

#endif // TST_IMAGEWRAPPERTEST_H

