#ifndef IMAGELIBRARYDEVIL_H
#define IMAGELIBRARYDEVIL_H

#include "Interfaces/IImageLibraryAdapter.h"
#include <QSize>

class ImageLibraryDevIL : public IImageLibraryAdapter
{
public:
    ImageLibraryDevIL();

    virtual quint32 genImage();
    virtual bool loadImage(QString fileName);
    virtual void deleteImage(quint32 imageName);

    virtual bool texImage24RGB(quint32 width, quint32 height, const char* data);
    virtual void setPixels24RGB(quint32 offsetX, quint32 offsetY,
                                quint32 width, quint32 height, const char* data);
    virtual void copyPixels24RGB(quint32 offsetX, quint32 offsetY,
                                 quint32 width, quint32 height, void* data);
    virtual void bindImage(quint32 imageName);

    virtual qint32 getWidth();
    virtual qint32 getHeight();
    virtual QByteArray getData();

    virtual void scale(quint32 width, quint32 heighr);
    virtual void rotate(quint32 angle);

    virtual void save(QString);
};

#endif // IMAGELIBRARYDEVIL_H
