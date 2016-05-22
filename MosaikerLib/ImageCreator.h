#ifndef IMAGECREATOR_H
#define IMAGECREATOR_H

#include <QImage>
#include <QThread>

class ImageCreator : public QThread
{
    Q_OBJECT

public:
    ImageCreator(QSize targetImageSize, QSize sliceSize, QStringList imageNames, QObject* parent = nullptr);

    void run() Q_DECL_OVERRIDE;

signals:
    void imageCreated(QImage image);

private:
    QStringList mImageNames;
    QSize mImageSize;
    QSize mSliceSize;
};

#endif // IMAGECREATOR_H
