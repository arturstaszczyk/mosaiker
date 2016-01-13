#include "tst_ResourcesDirModelTest.h"

#include <QtTest>
#include <QSignalSpy>

#include "tst_Common.h"
#include <Models/ResourcesDirModel.h>

ResourcesDirModelTest::ResourcesDirModelTest(QObject *parent) : QObject(parent)
{

}

void ResourcesDirModelTest::testIntegrationEmitOnValidDirectory()
{
    ResourcesDirModel resourcesDir;
    QSignalSpy spyResourceDir(&resourcesDir, SIGNAL(resourcesDirChanged(QString)));
    QSignalSpy spyIndexBuilt(&resourcesDir, SIGNAL(indexBuiltChanged(bool)));

    resourcesDir.setResourcesDir(TEST_RESOURCES_DIR);

    QCOMPARE(spyResourceDir.count(), 1);
    QCOMPARE(spyResourceDir.first().at(0).value<QString>(), QString(TEST_RESOURCES_DIR));

    QCOMPARE(spyIndexBuilt.count(), 1);
    QCOMPARE(spyIndexBuilt.first().at(0).value<bool>(), true);
}

void ResourcesDirModelTest::testEmitOnDirChange()
{
    ResourcesDirModel resourcesDir;
    QSignalSpy spy(&resourcesDir, SIGNAL(resourcesDirChanged(QString)));

    resourcesDir.setResourcesDir("test");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().at(0).value<QString>(), QString("test"));
}

void ResourcesDirModelTest::testEmitOnIndexBuiltChange()
{
    ResourcesDirModel resourcesDir;
    QSignalSpy spy(&resourcesDir, SIGNAL(indexBuiltChanged(bool)));

    resourcesDir.setIndexBuilt(true);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.first().at(0).value<bool>(), true);
}
