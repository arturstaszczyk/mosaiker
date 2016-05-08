#ifndef INDEXER_H
#define INDEXER_H

#include <QFile>
#include <QColor>
#include <QThread>

class ImageIndexer : public QThread
{
    Q_OBJECT
public:
    explicit ImageIndexer(QStringList imageList, QObject *parent = 0);

    void run() Q_DECL_OVERRIDE;
signals:
    void imageIndexed(QString fileName, quint32 colorValue);

private:
    QStringList mImageList;
};

#endif // INDEXER_H
