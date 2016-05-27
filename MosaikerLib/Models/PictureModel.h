#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QImage>
#include <QObject>
#include <QQuickImageProvider>

class PictureModel : public QObject, public QQuickImageProvider
{
    Q_OBJECT

public:
    Q_PROPERTY(QSize qmlSize READ qmlSize NOTIFY sizeChanged)
    Q_PROPERTY(bool displayImageLoaded READ isDisplayImageLoaded NOTIFY composedImageUpdated)
    Q_PROPERTY(bool overlayImageLoaded READ isOverlayImageLoaded NOTIFY composedImageUpdated)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)

public:
    explicit PictureModel(QObject *parent = 0);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    // Watch out, there is a non-const reference returned!!!
    QImage& displayImage() { return mDisplayImage; }
    QImage& overlayImage() { return mOverlayImage; }
    QImage& composedImage() { return mCompositionImage; }

    QSize qmlSize() const { return mQmlSize; }
    bool isDisplayImageLoaded() const { return !mDisplayImage.isNull(); }
    bool isOverlayImageLoaded() const { return !mOverlayImage.isNull(); }
    qreal opacity() const { return mImageOpacity; }

signals:
    void composedImageUpdated();
    void sizeChanged();
    void opacityChanged(qreal);

public slots:
    void setDisplayImage(const QImage& displayImage);
    void setOverlayImage(const QImage& displayImage);
    void setOpacity(qreal opacity);

private:
    void calculateSize(QSize* size, const QSize& requestedSize);
    void mergeDisplayWithOverlayImages();

private:
    QImage mDisplayImage;
    QImage mOverlayImage;
    QImage mCompositionImage;

    QSize mQmlSize;
    qreal mImageOpacity;
};

#endif // IMAGEMODEL_H
