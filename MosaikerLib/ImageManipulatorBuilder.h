#ifndef IMAGEMANIPULATORBUILDER_H
#define IMAGEMANIPULATORBUILDER_H

#include <QObject>

#include "Interfaces/ImageManipulatorInt.h"
#include "Interfaces/ImageLibraryAdapterInt.h"

class ImageManipulatorBuilder : public QObject
{
    Q_OBJECT
public:
    explicit ImageManipulatorBuilder(QObject *parent = 0);

    void setFilename(QString filename) { mFilename = filename; }
    ImageManipulatorInt* build(ImageLibraryAdapterInt& imageLibrary);

private:
    QString mFilename;
};

#endif // IMAGEMANIPULATORBUILDER_H
