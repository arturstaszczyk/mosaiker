#ifndef IMAGEMANIPULATORBUILDER_H
#define IMAGEMANIPULATORBUILDER_H

#include <QObject>
#include <QSize>
#include <QByteArray>

#include "Interfaces/IImageManipulator.h"
#include "Interfaces/IImageLibraryAdapter.h"

class ImageManipulatorBuilder : public QObject
{
    Q_OBJECT
public:
    explicit ImageManipulatorBuilder(IImageLibraryAdapter& imageLibrary,
                                     QObject *parent = 0);

    virtual void setFilename(QString filename) { mFilename = filename; }
    virtual void setSize(const QSize& size) { mSize = size; }
    virtual void setBytes(const QByteArray& bytes) { mBytes = bytes; }

    virtual IImageManipulator* build();

protected:
    IImageLibraryAdapter& mImageLibrary;
    QString mFilename;
    QSize mSize;
    QByteArray mBytes;
};

#endif // IMAGEMANIPULATORBUILDER_H
