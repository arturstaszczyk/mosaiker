#ifndef IMAGELIBRARYADAPTERMOCK_H
#define IMAGELIBRARYADAPTERMOCK_H

#include "MockBase.h"
#include "ImageLibraryAdapter.h"

#include <QObject>

class ImageLibraryAdapterMock : public ImageLibraryAdapter, public MockBase
{
    Q_OBJECT

public:
    virtual quint32 genImage()
    {
        CALL;
        return 42;
    }

    virtual bool loadImage(QString name)
    {
        CALL; ARG(name);
        return true;
    }


    virtual void deleteImage(quint32 name)
    {
        CALL; ARG(name);
    }

    virtual bool texImage24RGB(quint32 width, quint32 height, const char* data)
    {
        CALL; ARG(width), ARG(height), ARG(data);
        return true;
    }

    virtual void setPixels24RGB(quint32 offsetX, quint32 offsetY,
                                quint32 width, quint32 height, const char* data)
    {
        CALL; ARG(offsetX); ARG(offsetY); ARG(width); ARG(height); ARG(data);
    }

    virtual void copyPixels24RGB(quint32 offsetX, quint32 offsetY,
                                 quint32 width, quint32 height, char* data)
    {
        CALL; ARG(offsetX); ARG(offsetY); ARG(width); ARG(height); ARG(data);
    }

    virtual void bindImage(quint32 name)
    {
        CALL; ARG(name);
    }

    virtual quint32 getWidth() { CALL; return 0; }
    virtual quint32 getHeight() { CALL; return 0; }
    virtual const char* getData() { CALL; return nullptr; }

    virtual void scale(quint32 width, quint32 height)
    {
        CALL; ARG(width); ARG(height);
    }

    virtual void rotate(quint32 angle)
    {
        CALL; ARG(angle);
    }

    virtual void save(QString fileName)
    {
        CALL; ARG(fileName);
    }
};

#endif // IMAGELIBRARYADAPTERMOCK_H
