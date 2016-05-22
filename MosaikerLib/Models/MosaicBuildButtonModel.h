#ifndef MOSAICBUILDBUTTONMODEL_H
#define MOSAICBUILDBUTTONMODEL_H

#include <QObject>

class MosaicBuildButtonModel : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(bool isBeingCreated MEMBER mIsBeingCreated WRITE setIsBeingCreated NOTIFY isBeingCreatedChanged)

public:
    explicit MosaicBuildButtonModel(QObject *parent = 0);

    void setIsBeingCreated(bool isBeingCreated);

signals:
    void isBeingCreatedChanged(bool);

private:
    bool mIsBeingCreated;
};

#endif // MOSAICBUILDBUTTONMODEL_H
