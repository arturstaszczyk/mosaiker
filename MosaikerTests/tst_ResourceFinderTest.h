#ifndef TST_RESOURCEFINDERTEST_H
#define TST_RESOURCEFINDERTEST_H

#include <QObject>

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

#endif // TST_RESOURCEFINDERTEST_H

