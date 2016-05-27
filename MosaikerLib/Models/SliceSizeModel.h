#ifndef SLICESIZEMODEL_H
#define SLICESIZEMODEL_H

#include <QSize>
#include <QObject>

class SliceSizeModel : public QObject
{
    Q_OBJECT
public:
    explicit SliceSizeModel(QObject *parent = 0);

    Q_PROPERTY(quint32 sliceSize READ sliceSize WRITE setSliceSize NOTIFY sliceSizeChanged)

    quint32 sliceSize() const { return mSliceSize; }

signals:
    void sliceSizeChanged(quint32);

public slots:
    void setSliceSize(quint32 size);

private:
    quint32 mSliceSize;
};

#endif // SLICESIZEMODEL_H
