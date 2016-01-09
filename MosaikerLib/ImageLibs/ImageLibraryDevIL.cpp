#include "ImageLibraryDevIL.h"

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

ImageLibraryDevIL::ImageLibraryDevIL()
{
    ilInit();
    iluInit();
    ilEnable(IL_FILE_OVERWRITE);
}

quint32 ImageLibraryDevIL::genImage()
{
    return ilGenImage();
}

bool ImageLibraryDevIL::loadImage(QString fileName)
{
    const char* fileNameStr = fileName.toStdString().c_str();
    bool loaded = ilLoadImage(fileNameStr);
    if(loaded)
    {
        mSize.setWidth(ilGetInteger(IL_IMAGE_WIDTH));
        mSize.setHeight(ilGetInteger(IL_IMAGE_HEIGHT));
    }

    return loaded;
}

void ImageLibraryDevIL::deleteImage(quint32 imageName)
{
    ilDeleteImage(imageName);
}

bool ImageLibraryDevIL::texImage24RGB(quint32 width, quint32 height, const char* data)
{
    return false;
}

void ImageLibraryDevIL::setPixels24RGB(quint32 offsetX, quint32 offsetY,
                    quint32 width, quint32 height, const char* data)
{

}

void ImageLibraryDevIL::copyPixels24RGB(quint32 offsetX, quint32 offsetY,
                     quint32 width, quint32 height, char* data)
{
    ilCopyPixels(offsetX, offsetY, 0, width, height, 1, IL_RGB, IL_UNSIGNED_BYTE, data);
}

void ImageLibraryDevIL::bindImage(quint32 imageName)
{
    ilBindImage(imageName);
}

qint32 ImageLibraryDevIL::getWidth()
{
    return mSize.width();
}

qint32 ImageLibraryDevIL::getHeight()
{
    return mSize.height();
}

QByteArray ImageLibraryDevIL::getData()
{
    return QByteArray();
}

void ImageLibraryDevIL::scale(quint32 width, quint32 heighr)
{

}

void ImageLibraryDevIL::rotate(quint32 angle)
{

}

void ImageLibraryDevIL::save(QString)
{

}
