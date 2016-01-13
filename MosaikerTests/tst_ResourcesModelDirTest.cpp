#include "tst_ResourcesModelDirTest.h"

#include <QtTest>
#include <QSignalSpy>

#include <Models/ResourcesDirModel.h>

ResourcesModelDirTest::ResourcesModelDirTest(QObject *parent) : QObject(parent)
{

}

void ResourcesModelDirTest::testEmitOnDirChange()
{
    ResourcesDirModel resourcesDir;
    QSignalSpy spy(&resourcesDir, SIGNAL(resourcesDirChanged(QString)));

    resourcesDir.setResourcesDir("test");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().at(0).value<QString>(), QString("test"));
}

void ResourcesModelDirTest::testEmitOnIndexBuiltChange()
{
    ResourcesDirModel resourcesDir;
    QSignalSpy spy(&resourcesDir, SIGNAL(indexBuiltChanged(bool)));

    resourcesDir.setIndexBuilt(true);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().at(0).value<bool>(), true);
}
