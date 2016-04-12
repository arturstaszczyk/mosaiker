#ifndef INDEXER_H
#define INDEXER_H

#include <QFile>
#include <QColor>
#include <QObject>

class ImageIndexer : public QObject
{
    Q_OBJECT
public:
    explicit ImageIndexer(QStringList imageList, QObject *parent = 0);

    void execute();

signals:
    void imageIndexed(QString fileName, QRgb colorValue);

private:
    const QStringList& mImageList;
};

#endif // INDEXER_H
