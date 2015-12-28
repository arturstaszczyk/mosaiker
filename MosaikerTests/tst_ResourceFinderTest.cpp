#ifndef __TST_RESOURCE_FINDER_H__
#define __TST_RESOURCE_FINDER_H__

#include <QString>
#include <QtTest>

#include "ResourceFinder.h"
#include "Exceptions.h"

#define TEST_RESOURCES_DIR QString("./TestResources")

class ResourceFinderTest : public QObject
{
    Q_OBJECT

public:
    ResourceFinderTest()
    {}

private Q_SLOTS:
    void testFindAllResources();
    void testDirectoryNotExists();
    void testResourcesCleared();
    void testAddSingleFilter();
    void testMultipleAddFilters();
    void testSetFilters();
    void testFoundResources();
};

void ResourceFinderTest::testFindAllResources()
{
    ResourceFinder finder(TEST_RESOURCES_DIR);
    finder.find();

    QCOMPARE(finder.resourcesCount(), 3u);
}

void ResourceFinderTest::testDirectoryNotExists()
{
    ResourceFinder finder("./no_exists");
    QVERIFY_EXCEPTION_THROWN(finder.find(), ResourcesDirDoNotExists);
}

void ResourceFinderTest::testResourcesCleared()
{
    ResourceFinder finder(TEST_RESOURCES_DIR);
    finder.find();
    finder.find();

    QCOMPARE(finder.resourcesCount(), 3u);
}

void ResourceFinderTest::testAddSingleFilter()
{
    ResourceFinder finder(TEST_RESOURCES_DIR);

    finder.addFilter("*.png");
    finder.find();
    QCOMPARE(finder.resourcesCount(), 1u);

    finder.addFilter("*.jpg");
    finder.find();
    QCOMPARE(finder.resourcesCount(), 3u);

    finder.clearFilters();
    finder.addFilter("*.jpg");
    finder.find();
    QCOMPARE(finder.resourcesCount(), 2u);
}

void ResourceFinderTest::testMultipleAddFilters()
{
    ResourceFinder finder(TEST_RESOURCES_DIR);

    finder.addFilter("*.png");
    finder.find();
    QCOMPARE(finder.resourcesCount(), 1u);

    finder.addFilter({"*.png", "*.jpg"});
    finder.find();
    QCOMPARE(finder.resourcesCount(), 3u);
}

void ResourceFinderTest::testSetFilters()
{
    ResourceFinder finder(TEST_RESOURCES_DIR);

    finder.addFilter({"*.png", "*.jpg"});
    finder.setFilter("*.jpg");
    finder.find();
    QCOMPARE(finder.resourcesCount(), 2u);

    finder.setFilter({"*.jpg", "*.png"});
    finder.find();
    QCOMPARE(finder.resourcesCount(), 3u);
}

void ResourceFinderTest::testFoundResources()
{
    ResourceFinder finder(TEST_RESOURCES_DIR);
    finder.setFilter("*.png");
    finder.find();

    QStringList expected {
        TEST_RESOURCES_DIR + "/res1.png"
    };
    QCOMPARE(finder.resourcesList(), expected);

    finder.setFilter("*.jpeg");
    finder.find();

    expected = QStringList {};
    QCOMPARE(finder.resourcesList(), expected);

    expected = QStringList{
        TEST_RESOURCES_DIR + "/res1.jpg",
        TEST_RESOURCES_DIR + "/res2.jpg"
    };

    finder.setFilter("*.jpg");
    finder.find();
    QCOMPARE(finder.resourcesList(), expected);
}

#include "tst_ResourceFinderTest.moc"

#endif // __TST_RESOURCE_FINDER_H__
