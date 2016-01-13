#include "tst_CommandOpenResourcesDirTest.h"

#include <QtTest>
#include <QSignalSpy>

#include "Exceptions.h"
#include "mocks/FileChooserMock.h"

#include "Commands/CommandOpenResourcesDir.h"

CommandOpenResourcesDirTest::CommandOpenResourcesDirTest(QObject *parent) : QObject(parent)
{

}

void CommandOpenResourcesDirTest::testInvalidDir()
{
    FileChooserMock fileChooser;
    fileChooser.returnValues("chooseDir", { "./invalid_path" });
    CommandOpenResourcesDir command(fileChooser);
    QSignalSpy spy(&command, SIGNAL(dirOpened(QString)));

    QVERIFY_EXCEPTION_THROWN(command.execute(), PathDoNotExists);
    QCOMPARE(spy.count(), 0);
}

void CommandOpenResourcesDirTest::testOpenDir()
{
    FileChooserMock fileChooser;
    fileChooser.returnValues("chooseDir", { "./" });
    CommandOpenResourcesDir command(fileChooser);

    QSignalSpy spy(&command, SIGNAL(dirOpened(QString)));
    command.execute();

    QCOMPARE(spy.count(), 1);

    QString dirName = spy.first().at(0).value<QString>();
    QCOMPARE(dirName, QString("./"));
}
