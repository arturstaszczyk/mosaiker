#ifndef IMAGEMANIPULATORBUILDER_H
#define IMAGEMANIPULATORBUILDER_H

#include <QObject>
#include <QSize>
#include <QByteArray>

#include "Interfaces/ImageManipulatorInt.h"
#include "Interfaces/ImageLibraryAdapterInt.h"

class ImageManipulatorBuilder : public QObject
{
    Q_OBJECT
public:
    explicit ImageManipulatorBuilder(ImageLibraryAdapterInt& imageLibrary,
                                     QObject *parent = 0);

    virtual void setFilename(QString filename) { mFilename = filename; }
    virtual void setSize(const QSize& size) { mSize = size; }
    virtual void setBytes(const QByteArray& bytes) { mBytes = bytes; }

    virtual ImageManipulatorInt* build();

protected:
    ImageLibraryAdapterInt& mImageLibrary;
    QString mFilename;
    QSize mSize;
    QByteArray mBytes;
};

#endif // IMAGEMANIPULATORBUILDER_H
