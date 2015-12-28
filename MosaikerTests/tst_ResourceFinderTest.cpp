#include <QString>
#include <QtTest>

#include "ResourceFinder.h"
#include "Exceptions.h"

#define TEST_RESOURCES_DIR "./TestResources"

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
    void testSingleFilter();
    void testMultipleFilters();
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

void ResourceFinderTest::testSingleFilter()
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

void ResourceFinderTest::testMultipleFilters()
{
    ResourceFinder finder(TEST_RESOURCES_DIR);

    finder.addFilter({"*.png", "*.jpg"});
    finder.find();
    QCOMPARE(finder.resourcesCount(), 3u);
}

QTEST_APPLESS_MAIN(ResourceFinderTest)

#include "tst_ResourceFinderTest.moc"
