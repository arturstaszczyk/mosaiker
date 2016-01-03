#include "tst_CommandOpenImageTest.h"

#include <QSignalSpy>

#include "mocks/ImageLibraryAdapterMock.h"

void CommandOpenImageTest::testOpenImageSignal()
{
    ImageLibraryAdapterMock mock;
    mock.returnValues("loadImage", { true });
    mock.returnValues("toQImage", { QImage() });

    Command* command = new CommandOpenImage(mock);
    command.execute();

    QSignalSpy spy(&command, SIGNAL(imageOpened(QImage)));

    QCOMPARE(spy.count(), 1);
}
