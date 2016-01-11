#ifndef IMAGELIBRARYADAPTERMOCK_H
#define IMAGELIBRARYADAPTERMOCK_H

#include <QtMock.h>
#include "Interfaces/IImageLibraryAdapter.h"

#include <QObject>

class ImageLibraryAdapterMock : public IImageLibraryAdapter, public QtMockExt::QtMock
{

public:
    virtual quint32 genImage()
    {
        MOCK_CALL;
        return RETURN_VALUES(quint32);
    }

    virtual bool loadImage(QString name)
    {
        MOCK_CALL; MOCK_ARG(MOCK_FNAME, name);
        return RETURN_VALUES(bool);
    }


    virtual void deleteImage(quint32 name)
    {
        MOCK_CALL; MOCK_ARG(MOCK_FNAME, name);
    }

    virtual bool texImage24RGB(quint32 width, quint32 height, const char* data)
    {
        MOCK_CALL; MOCK_ARG(MOCK_FNAME, width); MOCK_ARG(MOCK_FNAME, height);
        MOCK_ARG(MOCK_FNAME, data);
        return RETURN_VALUES(bool);
    }

    virtual void setPixels24RGB(quint32 offsetX, quint32 offsetY,
                                quint32 width, quint32 height, const char* data)
    {
        MOCK_CALL;
        MOCK_ARG(MOCK_FNAME, offsetX); MOCK_ARG(MOCK_FNAME, offsetY);
        MOCK_ARG(MOCK_FNAME, width); MOCK_ARG(MOCK_FNAME, height);
        MOCK_ARG(MOCK_FNAME, data);
    }

    virtual void copyPixels24RGB(quint32 offsetX, quint32 offsetY,
                                 quint32 width, quint32 height, void* data)
    {
        MOCK_CALL;
        MOCK_ARG(MOCK_FNAME, offsetX); MOCK_ARG(MOCK_FNAME, offsetY);
        MOCK_ARG(MOCK_FNAME, width); MOCK_ARG(MOCK_FNAME, height);
        MOCK_ARG(MOCK_FNAME, QVariant::fromValue(data));
    }

    virtual void bindImage(quint32 name)
    {
        MOCK_CALL; MOCK_ARG(MOCK_FNAME, name);
    }

    virtual qint32 getWidth() { MOCK_CALL; return RETURN_VALUES(quint32); }
    virtual qint32 getHeight() { MOCK_CALL; return RETURN_VALUES(quint32); }
    virtual QByteArray getData() { MOCK_CALL; return RETURN_VALUES(QByteArray); }

    virtual void scale(quint32 width, quint32 height)
    {
        MOCK_CALL; MOCK_ARG(MOCK_FNAME, width); MOCK_ARG(MOCK_FNAME, height);
    }

    virtual void rotate(quint32 angle)
    {
        MOCK_CALL; MOCK_ARG(MOCK_FNAME, angle);
    }

    virtual void save(QString fileName)
    {
        MOCK_CALL; MOCK_ARG(MOCK_FNAME, fileName);
    }
};

#endif // IMAGELIBRARYADAPTERMOCK_H
