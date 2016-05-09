#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QImage>
#include <QObject>
#include <QQuickImageProvider>

class MainImageModel : public QObject, public QQuickImageProvider
{
    Q_OBJECT

public:
    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)
    Q_PROPERTY(bool loaded READ isLoaded NOTIFY imageUpdated)

public:
    explicit MainImageModel(QObject *parent = 0);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    QSize size() const { return mDesiredSize; }
    bool isLoaded() const { return mOriginalImage.size().isValid(); }

signals:
    void imageUpdated();
    void sizeChanged();

public slots:
    void setMainImage(const QImage& image);

private:
    QImage mOriginalImage;
    QSize mDesiredSize;
};

#endif // IMAGEMODEL_H
