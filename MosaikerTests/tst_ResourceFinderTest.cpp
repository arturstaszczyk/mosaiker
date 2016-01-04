#include "tst_ResourceFinderTest.h"

#include <QString>
#include <QtTest>

#include "tst_Common.h"
#include "Exceptions.h"
#include "ResourceFinder.h"

void ResourceFinderTest::testFindAllResources()
{
    ResourceFinder* finderObj = new ResourceFinder(TEST_RESOURCES_DIR);
    finderObj->find();

    QCOMPARE(finderObj->resourcesCount(), 3u);
}

void ResourceFinderTest::testDirectoryNotExists()
{
    ResourceFinder* finderObj = new ResourceFinder("./no_exists");
    QVERIFY_EXCEPTION_THROWN(finderObj->find(), ResourcesDirDoNotExists);
}

void ResourceFinderTest::testResourcesCleared()
{
    ResourceFinder* finderObj = new ResourceFinder(TEST_RESOURCES_DIR);
    finderObj->find();
    finderObj->find();

    QCOMPARE(finderObj->resourcesCount(), 3u);
}

void ResourceFinderTest::testAddSingleFilter()
{
    ResourceFinder* finderObj = new ResourceFinder(TEST_RESOURCES_DIR);

    finderObj->addFilter("*.png");
    finderObj->find();
    QCOMPARE(finderObj->resourcesCount(), 1u);

    finderObj->addFilter("*.jpg");
    finderObj->find();
    QCOMPARE(finderObj->resourcesCount(), 3u);

    finderObj->clearFilters();
    finderObj->addFilter("*.jpg");
    finderObj->find();
    QCOMPARE(finderObj->resourcesCount(), 2u);
}

void ResourceFinderTest::testMultipleAddFilters()
{
    ResourceFinder* finderObj = new ResourceFinder(TEST_RESOURCES_DIR);

    finderObj->addFilter("*.png");
    finderObj->find();
    QCOMPARE(finderObj->resourcesCount(), 1u);

    finderObj->addFilter({"*.png", "*.jpg"});
    finderObj->find();
    QCOMPARE(finderObj->resourcesCount(), 3u);
}

void ResourceFinderTest::testSetFilters()
{
    ResourceFinder* finderObj = new ResourceFinder(TEST_RESOURCES_DIR);

    finderObj->addFilter({"*.png", "*.jpg"});
    finderObj->setFilter("*.jpg");
    finderObj->find();
    QCOMPARE(finderObj->resourcesCount(), 2u);

    finderObj->setFilter({"*.jpg", "*.png"});
    finderObj->find();
    QCOMPARE(finderObj->resourcesCount(), 3u);
}

void ResourceFinderTest::testFoundResources()
{
    ResourceFinder* finderObj = new ResourceFinder(TEST_RESOURCES_DIR);
    finderObj->setFilter("*.png");
    finderObj->find();

    QStringList expected {
        TEST_RESOURCES_DIR + "/res1.png"
    };
    QCOMPARE(finderObj->resourcesList(), expected);

    finderObj->setFilter("*.jpeg");
    finderObj->find();

    expected = QStringList {};
    QCOMPARE(finderObj->resourcesList(), expected);

    expected = QStringList{
        TEST_RESOURCES_DIR + "/res1.jpg",
        TEST_RESOURCES_DIR + "/res2.jpg"
    };

    finderObj->setFilter("*.jpg");
    finderObj->find();
    QCOMPARE(finderObj->resourcesList(), expected);
}

//#include "tst_ResourceFinderTest.moc"
