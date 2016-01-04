#ifndef IMAGEMANIPULATORBUILTERTEST_H
#define IMAGEMANIPULATORBUILTERTEST_H

#include <QObject>

#include "tst_Common.h"
#include "mocks/ImageLibraryAdapterMock.h"

class ImageManipulatorBuilderTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void testBuilder();
    void testThrowsOnBadImage();
    void testThrowsOnBadPath();

private:
    ImageLibraryAdapterMock* mLibraryAdapter;
};

#endif // IMAGEMANIPULATORBUILTERTEST_H
