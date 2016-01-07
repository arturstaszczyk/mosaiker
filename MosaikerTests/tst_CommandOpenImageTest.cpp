#include "tst_CommandOpenImageTest.h"

#include <QImage>
#include <QSignalSpy>
#include <QFileDialog>
#include <QObject>

#include "Commands/CommandOpenImage.h"
#include "ImageManipulator.h"

#include "mocks/FileChooserMock.h"
#include "mocks/QFileDialogMock.h"
#include "mocks/ImageLibraryAdapterMock.h"
#include "mocks/ImageManipulatorBuilderMock.h"

void CommandOpenImageTest::testOpenImageSignal()
{
    ImageLibraryAdapterMock imageLibraryMock;
    ImageManipulatorBuilderMock builder(imageLibraryMock);

    FileChooserMock fileChooserMock;

    CommandOpenImage* command = new CommandOpenImage(builder, fileChooserMock);
    QSignalSpy spy(command, SIGNAL(imageOpened(QImage)));
    command->execute();

    QCOMPARE(spy.count(), 1);
}
