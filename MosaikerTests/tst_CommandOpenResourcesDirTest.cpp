﻿#include "tst_CommandOpenResourcesDirTest.h"

#include <QtTest>

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

    QVERIFY_EXCEPTION_THROWN(command.execute(), PathDoNotExists);
}
