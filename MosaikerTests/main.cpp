#include <QtTest>

#include "tst_ResourceFinderTest.h"
#include "tst_ImageWrapperTest.h"

int main(int argc, char *argv[])
{
    int status = 0;

    QTEST_SET_MAIN_SOURCE_PATH

    ResourceFinderTest resourceFinderTest;
    status |= QTest::qExec(&resourceFinderTest, argc, argv);

    ImageWrapperTest imageWrapperTest;
    status |= QTest::qExec(&imageWrapperTest, argc, argv);

    return status;
}
