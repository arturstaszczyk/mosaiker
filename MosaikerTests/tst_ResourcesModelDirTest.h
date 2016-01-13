#ifndef RESOURCESMODELDIRTEST_H
#define RESOURCESMODELDIRTEST_H

#include <QObject>

class ResourcesModelDirTest : public QObject
{
    Q_OBJECT
public:
    explicit ResourcesModelDirTest(QObject *parent = 0);

private slots:
    void testEmitOnDirChange();
    void testEmitOnIndexBuiltChange();

};

#endif // RESOURCESMODELDIRTEST_H
