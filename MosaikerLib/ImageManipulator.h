#ifndef IMAGEMANIPULATOR_H
#define IMAGEMANIPULATOR_H

#include <QSize>
#include <QRect>
#include <QObject>

#include "ImageLibraryAdapter.h"

class ImageManipulator : public QObject
{
    Q_OBJECT

public:
    explicit ImageManipulator(const QSize& size, ImageLibraryAdapter& imageLibrary,
                              QObject *parent = nullptr);

    explicit ImageManipulator(QString filename, ImageLibraryAdapter& imageLibrary,
                              QObject* parent = nullptr);

    explicit ImageManipulator(const QSize& size, QByteArray data, ImageLibraryAdapter& imageLibrary,
                              QObject* parent = nullptr);

    virtual ~ImageManipulator();

    ImageManipulator* imageManipulatorForSubimage(const QRect& imageRect);

    void resize(const QSize& newSize);

    quint32 imageName() const { return mImageName; }
    qint32 width() const { return mImageSize.width(); }
    qint32 height() const { return mImageSize.height(); }
    const ImageLibraryAdapter& imageLibraryAdapter() const { return mImageLibraryObj; }

public:
    static const int IMAGE_CHANNELS_3;

private:
    ImageLibraryAdapter& mImageLibraryObj;

    quint32 mImageName;
    QSize mImageSize;
};

#endif // IMAGEMANIPULATOR_H
