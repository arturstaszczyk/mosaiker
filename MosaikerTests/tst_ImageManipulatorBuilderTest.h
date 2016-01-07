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

    void testBuilderFromFile();
    void testThrowsOnBadImage();
    void testThrowsOnBadPath();

    void testBuilderEmpty();
    void testBuildFromBytes();

    void testThrowsOnNotEnoughData();

private:
    ImageLibraryAdapterMock* mLibraryAdapter;
};

#endif // IMAGEMANIPULATORBUILTERTEST_H
