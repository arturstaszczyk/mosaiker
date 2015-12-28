#include <QtTest>

#include "tst_ResourceFinderTest.cpp"

int main(int argc, char *argv[])
{
    int status = 0;

    QTEST_SET_MAIN_SOURCE_PATH

    ResourceFinderTest tc;
    status |= QTest::qExec(&tc, argc, argv);

    return status;
}
