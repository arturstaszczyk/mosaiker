﻿#ifndef MOSAICBUILDBUTTONMODEL_H
#define MOSAICBUILDBUTTONMODEL_H

#include <QObject>

class MosaicBuildButtonModel : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(bool isBeingCreated MEMBER mIsBeingCreated WRITE setIsBeingCreated NOTIFY isBeingCreatedChanged)
    Q_PROPERTY(bool wasCreated MEMBER mWasCreated WRITE setWasCreated NOTIFY wasCreatedChanged)

public:
    explicit MosaicBuildButtonModel(QObject *parent = 0);

    void setIsBeingCreated(bool isBeingCreated);
    void setWasCreated(bool wasCreated);

signals:
    void isBeingCreatedChanged(bool);
    void wasCreatedChanged(bool);

private:
    bool mIsBeingCreated;
    bool mWasCreated;
};

#endif // MOSAICBUILDBUTTONMODEL_H
