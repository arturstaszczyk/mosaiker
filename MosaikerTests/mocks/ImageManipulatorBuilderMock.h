#ifndef IMAGEMANIPULATORBUILDERMOCK_H
#define IMAGEMANIPULATORBUILDERMOCK_H

#include "ImageManipulatorBuilder.h"
#include <QtMock.h>
#include "ImageManipulator.h"

class ImageManipulatorBuilderMock : public ImageManipulatorBuilder,
        public QtMockExt::QtMock
{
public:
    ImageManipulatorBuilderMock(IImageLibraryAdapter& imageLibrary)
        : ImageManipulatorBuilder(imageLibrary)
    {

    }

    IImageManipulator* build() override
    {
        MOCK_CALL;
        return new ImageManipulator(QSize(32, 32), mImageLibrary);
    }
};

#endif // IMAGEMANIPULATORBUILDERMOCK_H
