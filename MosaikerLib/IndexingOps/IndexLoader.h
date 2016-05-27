#ifndef INDEXLOADER_H
#define INDEXLOADER_H

#include <QObject>
#include <QColor>

#include "Interfaces/IIndexLoader.h"

class IndexLoader : public QObject, public IIndexLoader
{
    Q_OBJECT
private:
    struct Index
    {
        QRgb index;
        QString fileName;

        quint32 distanceToIndex(QRgb other) const
        {
            return abs(qRed(index) - qRed(other)) +
                    abs(qGreen(index) - qGreen(other)) +
                    abs(qBlue(index) - qBlue(other));
        }
    };

public:

    explicit IndexLoader(QString indexFileName, QObject *parent = 0);

    virtual void loadIndex() override;

    virtual QString closestFileNameByIndex(quint32 index) override;
    virtual QString closestFileNameByIndexExcluding(quint32 index, QStringList excludes) override;

private:
    QString mIndexFileName;
    QList<Index> mFileIndex;
};

#endif // INDEXLOADER_H
