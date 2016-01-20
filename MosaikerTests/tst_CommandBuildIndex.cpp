#include "tst_CommandBuildIndex.h"

#include <QtTest>
#include <QSignalSpy>

#include "tst_Common.h"
#include "mocks/ResourceFinderMock.h"

#include "Commands/CommandBuildIndex.h"

CommandBuildIndexTest::CommandBuildIndexTest(QObject *parent) : QObject(parent)
{

}

void CommandBuildIndexTest::testBuildIndex()
{
    ResourceFinderMock finderMock(TEST_RESOURCES_DIR);

    CommandBuildIndex buildIndex(finderMock);
    buildIndex.execute();

    QVERIFY(finderMock.hasExactlyOneCall("find"));
}
