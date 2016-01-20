#include "tst_CommandBuildIndex.h"

#include <QtTest>
#include <QSignalSpy>

CommandBuildIndexTest::CommandBuildIndexTest(QObject *parent) : QObject(parent)
{

}


void CommandBuildIndexTest::testBuildIndex()
{
    ResourceFinderMock finderMock;

    CommandBuildIndex buildIndex(finder);
    buildIndex.execute();

    QVERIFY(finderMock.hasExactlyOneCal());
}
