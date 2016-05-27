#ifndef SLICESIZEMODEL_H
#define SLICESIZEMODEL_H

#include <QSize>
#include <QObject>

class SliceSizeModel : public QObject
{
    Q_OBJECT
public:
    explicit SliceSizeModel(QObject *parent = 0);

    Q_PROPERTY(QSize sliceSize READ sliceSize WRITE setSliceSize NOTIFY sliceSizeChanged)

    void setSliceSize(QSize size);
    QSize sliceSize() const { return mSliceSize; }

signals:
    void sliceSizeChanged(QSize);

public slots:
    void updateSliceSize(QSize sliceSize);

private:
    QSize mSliceSize;
};

#endif // SLICESIZEMODEL_H
