#ifndef IMAGEMANIPULATOR_H
#define IMAGEMANIPULATOR_H

#include <QSize>
#include <QRect>
#include <QObject>

#include "Interfaces/ImageManipulatorInt.h"
#include "Interfaces/ImageLibraryAdapterInt.h"

class ImageManipulator : public QObject, public ImageManipulatorInt
{
    Q_OBJECT

public:
    explicit ImageManipulator(const QSize& size, ImageLibraryAdapterInt& imageLibrary,
                              QObject *parent = nullptr);

    explicit ImageManipulator(QString filename, ImageLibraryAdapterInt& imageLibrary,
                              QObject* parent = nullptr);

    explicit ImageManipulator(const QSize& size, QByteArray data, ImageLibraryAdapterInt& imageLibrary,
                              QObject* parent = nullptr);

    virtual ~ImageManipulator();

    ImageManipulator* imageManipulatorForSubimage(const QRect& imageRect) override;
    void saveAsPng(QString fileName) override;
    QImage toQImage() const override;

    void resize(const QSize& newSize) override;
    QByteArray rawData() override;

    quint32 imageName() const override { return mImageName; }
    qint32 width() const override { return mImageSize.width(); }
    qint32 height() const override { return mImageSize.height(); }
    const ImageLibraryAdapterInt& imageLibraryAdapter() const override { return mImageLibraryObj; }

public:
    static const int IMAGE_CHANNELS_3;

private:
    ImageLibraryAdapterInt& mImageLibraryObj;

    quint32 mImageName;
    QSize mImageSize;
};

#endif // IMAGEMANIPULATOR_H
