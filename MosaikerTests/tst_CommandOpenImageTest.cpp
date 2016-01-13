#include "tst_CommandOpenImageTest.h"

#include <QImage>
#include <QSignalSpy>
#include <QFileDialog>
#include <QObject>


#include "tst_Common.h"
#include "Exceptions.h"
#include "Commands/CommandOpenImage.h"
#include "mocks/FileChooserMock.h"

void CommandOpenImageTest::testInvalidImage()
{
    FileChooserMock fileChooserMock;

    CommandOpenImage command(fileChooserMock);
    QSignalSpy spy(&command, SIGNAL(imageOpened(QImage)));

    QVERIFY_EXCEPTION_THROWN(command.execute(), CannotLoadImage);
    QCOMPARE(spy.count(), 0);
}

void CommandOpenImageTest::testImageOpened()
{
    FileChooserMock fileChooserMock;
    fileChooserMock.returnValues("chooseFile", { TEST_RESOURCES_DIR + "/res1.png" });
    CommandOpenImage command(fileChooserMock);

    QSignalSpy spy(&command, SIGNAL(imageOpened(QImage)));
    command.execute();

    QCOMPARE(spy.count(), 1);
    QVariantList args = spy.first();

    QImage image = args.at(0).value<QImage>();

    QCOMPARE(image.width(), 256);
    QCOMPARE(image.height(), 256);
}
