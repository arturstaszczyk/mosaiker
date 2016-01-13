#ifndef RESOURCESMODELDIRTEST_H
#define RESOURCESMODELDIRTEST_H

#include <QObject>

class ResourcesDirModelTest : public QObject
{
    Q_OBJECT
public:
    explicit ResourcesDirModelTest(QObject *parent = 0);

private slots:
    void testIntegrationEmitOnValidDirectory();
    void testEmitOnDirChange();
    void testEmitOnIndexBuiltChange();

};

#endif // RESOURCESMODELDIRTEST_H
