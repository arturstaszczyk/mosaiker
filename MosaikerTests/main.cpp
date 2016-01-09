#include <QtTest>

#include "tst_ImageModel.h"
#include "tst_ResourceFinderTest.h"
#include "tst_ImageManipulatorTest.h"
#include "tst_CommandOpenImageTest.h"
#include "tst_ImageManipulatorBuilderTest.h"

#define ADD_TEST(CLASS_NAME, STATUS, ARGC, ARGV) \
    { \
        CLASS_NAME classUnderTest; \
        STATUS |= QTest::qExec(&classUnderTest, ARGC, ARGV); \
    }

int main(int argc, char *argv[])
{
    int status = 0;

    QApplication test(argc, argv);

    QTEST_SET_MAIN_SOURCE_PATH;

    ADD_TEST(ResourceFinderTest, status, argc, argv);
    ADD_TEST(ImageManipulatorTest, status, argc, argv);
    ADD_TEST(ImageManipulatorBuilderTest, status, argc, argv);
    ADD_TEST(CommandOpenImageTest, status, argc, argv);
    ADD_TEST(ImageModelTest, status, argc, argv);

    return status;
}
