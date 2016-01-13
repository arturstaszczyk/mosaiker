#include "tst_CommandOpenResourcesDirTest.h"

#include <QtTest>

#include "Exceptions.h"
#include "mocks/FileChooserMock.h"

CommandOpenResourcesDirTest::CommandOpenResourcesDirTest(QObject *parent) : QObject(parent)
{

}

CommandOpenResourcesDirTest::testInvalidDir()
{
    FileChooserMock fileChooser;

    CommandOpenResourcesDir command(fileChooser);

    QVERIFY_EXCEPTION_THROWN(command.execute(), PathDoNotExists);
}
