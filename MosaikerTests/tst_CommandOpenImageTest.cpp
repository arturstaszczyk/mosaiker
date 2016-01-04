#include "tst_CommandOpenImageTest.h"

#include <QImage>
#include <QSignalSpy>
#include <QFileDialog>

#include "Commands/CommandOpenImage.h"

#include "mocks/ImageLibraryAdapterMock.h"
#include "mocks/QFileDialogMock.h"

void CommandOpenImageTest::testOpenImageSignal()
{
    ImageLibraryAdapterMock mock;
    mock.returnValues("loadImage", { true });
    mock.returnValues("toQImage", { QImage() });

    QFileDialogMock fileDialog;
    fileDialog.returnValues("exec", { true });
    fileDialog.returnValues("selectedFiles", { "test" });

    ImageManipulatorBuilder builder;
//    Command* command = new CommandOpenImage(builder, mock, fileDialog);
//    command->execute();

//    QSignalSpy spy(command, SIGNAL(imageOpened(QImage)));

//    QCOMPARE(spy.count(), 1);
}
