#ifndef IMAGEMANIPULATOR_H
#define IMAGEMANIPULATOR_H

#include <QSize>
#include <QRect>
#include <QObject>

#include "Interfaces/IImageManipulator.h"
#include "Interfaces/IImageLibraryAdapter.h"

class ImageManipulator : public QObject, public IImageManipulator
{
    Q_OBJECT

public:
    explicit ImageManipulator(const QSize& size, IImageLibraryAdapter& imageLibrary,
                              QObject *parent = nullptr);

    explicit ImageManipulator(QString filename, IImageLibraryAdapter& imageLibrary,
                              QObject* parent = nullptr);

    explicit ImageManipulator(const QSize& size, QByteArray data, IImageLibraryAdapter& imageLibrary,
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
    const IImageLibraryAdapter& imageLibraryAdapter() const override { return mImageLibraryObj; }

public:
    static const int IMAGE_CHANNELS_3;

private:
    IImageLibraryAdapter& mImageLibraryObj;

    quint32 mImageName;
    QSize mImageSize;

    QString name;
};

#endif // IMAGEMANIPULATOR_H
