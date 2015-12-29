#ifndef IMAGEMANIPULATOR_H
#define IMAGEMANIPULATOR_H

#include <QObject>
#include "ImageLibraryAdapter.h"

class ImageManipulator : public QObject
{
    Q_OBJECT
public:
    explicit ImageManipulator(quint32 width, quint32 height,
                              ImageLibraryAdapter* imageLibrary,
                              QObject *parent = nullptr);

    explicit ImageManipulator(QString fileName,
                              ImageLibraryAdapter* imageLibrary,
                              QObject* parent = nullptr);

    void resize(quint32 width, quint32 height);

    quint32 imageName() const { return mImageName; }
    quint32 width() const { return mWidth; }
    quint32 height() const { return mHeight; }
    ImageLibraryAdapter* imageLibraryAdapter() const { return mImageLibraryObj; }

protected:
    static const int IMAGE_CHANNELS_3;

private:
    ImageLibraryAdapter* mImageLibraryObj;

    quint32 mImageName;
    quint32 mWidth;
    quint32 mHeight;
};

#endif // IMAGEMANIPULATOR_H
