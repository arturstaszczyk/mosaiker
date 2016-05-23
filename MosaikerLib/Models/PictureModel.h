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
    Q_PROPERTY(bool displayImageLoaded READ isDisplayImageLoaded NOTIFY imageUpdated)
    Q_PROPERTY(bool overlayImageLoaded READ isOverlayImageLoaded NOTIFY imageUpdated)

public:
    explicit PictureModel(QObject *parent = 0);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    // Watch out, there is a non-const reference returned!!!
    QImage& displayImage() { return mDisplayImage; }
    QImage& overlayImage() { return mOverlayImage; }

    QSize qmlSize() const { return mQmlSize; }
    bool isDisplayImageLoaded() const { return !mDisplayImage.isNull(); }
    bool isOverlayImageLoaded() const { return !mOverlayImage.isNull(); }

signals:
    void imageUpdated();
    void sizeChanged();

public slots:
    void setDisplayImage(const QImage& displayImage);
    void setOverlayImage(const QImage& displayImage);

private:
    QImage mDisplayImage;
    QImage mOverlayImage;
    QImage mCompositionImage;

    QSize mQmlSize;
};

#endif // IMAGEMODEL_H
