#include "tst_CommandOpenImageTest.h"

#include <QImage>
#include <QSignalSpy>
#include <QFileDialog>

#include "Commands/CommandOpenImage.h"

#include "mocks/ImageLibraryAdapterMock.h"

void CommandOpenImageTest::testOpenImageSignal()
{
    ImageLibraryAdapterMock mock;
    mock.returnValues("loadImage", { true });
    mock.returnValues("toQImage", { QImage() });

    QFileDialog fileDialog;
    Command* command = new CommandOpenImage(mock, fileDialog);
    command->execute();

    QSignalSpy spy(command, SIGNAL(imageOpened(QImage)));

    QCOMPARE(spy.count(), 1);
}
