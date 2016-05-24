#ifndef INDEXBUILDER_H
#define INDEXBUILDER_H

#include <QObject>
#include <QByteArray>

#include "Interfaces/IIndexBuilder.h"

class IndexBuilder : public QObject, public IIndexBuilder
{
    Q_OBJECT
public:
    explicit IndexBuilder(QString indexFilename, QObject *parent = 0);

    virtual void addIndexForFilename(quint32 index, QString filename) override;
    virtual void save() override;

private:
    QByteArray mFileData;
    QString mIndexFilename;
};

#endif // INDEXBUILDER_H
