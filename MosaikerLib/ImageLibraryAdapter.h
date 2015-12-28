﻿#ifndef IMAGELIBRARYADAPTER_H
#define IMAGELIBRARYADAPTER_H

#include <QObject>

class ImageLibraryAdapter : public QObject
{
    Q_OBJECT

public:
    virtual quint32 genImage() = 0;
    virtual bool loadImage(QString) = 0;
    virtual void deleteImage(quint32) = 0;

    virtual bool texImage24RGB(quint32 width, quint32 height, const char* data) = 0;
    virtual void setPixels24RGB(quint32 offsetX, quint32 offsetY,
                                quint32 width, quint32 height, const char* data) = 0;
    virtual void copyPixels24RGB(quint32 offsetX, quint32 offsetY,
                                 quint32 width, quint32 height, char* data) = 0;
    virtual void bindImage(quint32) = 0;

    virtual quint32 getWidth() = 0;
    virtual quint32 getHeight() = 0;
    virtual const char* getData() = 0;

    virtual void scale(quint32 width, quint32 heighr) = 0;
    virtual void rotate(quint32 angle) = 0;

    virtual void save(QString) = 0;

};

#endif // IMAGELIBRARYADAPTER_H

