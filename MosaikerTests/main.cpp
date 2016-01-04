#include <QtTest>

#include "tst_ResourceFinderTest.h"
#include "tst_ImageManipulatorTest.h"
#include "tst_CommandOpenImageTest.h"
#include "tst_ImageManipulatorBuilderTest.h"

int main(int argc, char *argv[])
{
    int status = 0;

    QApplication test(argc, argv);

    QTEST_SET_MAIN_SOURCE_PATH

    ResourceFinderTest resourceFinderTest;
    status |= QTest::qExec(&resourceFinderTest, argc, argv);

    ImageManipulatorTest imageWrapperTest;
    status |= QTest::qExec(&imageWrapperTest, argc, argv);

    ImageManipulatorBuilderTest imageManipulatorBuilderTest;
    status |= QTest::qExec(&imageManipulatorBuilderTest, argc, argv);

    CommandOpenImageTest commandOpenImageTest;
    status |= QTest::qExec(&commandOpenImageTest, argc, argv);

    return status;
}
