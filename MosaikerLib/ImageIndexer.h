#ifndef INDEXER_H
#define INDEXER_H

#include <QFile>
#include <QList>
#include <QColor>
#include <Qimage>
#include <QThread>

class ImageIndexer : public QThread
{
    Q_OBJECT
public:
    explicit ImageIndexer(QStringList imageList, QObject *parent = 0);
    explicit ImageIndexer(QList<QImage> imageList, QObject *parent = 0);

    void run() Q_DECL_OVERRIDE;

private:
    void runWithImageNames();
    void runWithImageList();

    QRgb calculateImageIndex(QImage image);

signals:
    void imageIndexed(QString fileName, quint32 colorValue);

private:
    QStringList mImageNamesList;
    QList<QImage> mImagesList;
};

#endif // INDEXER_H
