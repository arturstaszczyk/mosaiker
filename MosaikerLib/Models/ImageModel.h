#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QImage>
#include <QObject>
#include <QQuickImageProvider>

class ImageModel : public QObject, public QQuickImageProvider
{
    Q_OBJECT
public:
    explicit ImageModel(QObject *parent = 0);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

signals:

public slots:

    void setOriginalImage(const QImage& image);
};

#endif // IMAGEMODEL_H
