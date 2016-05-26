#include "MainWindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QtGlobal>

#include <string>

#include <HptIntegration.h>

#ifdef _PROFILE
std::string PROFILE_FILENAME = "../../../profile.dat";
#endif

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto ret = a.exec();
    PROFILE_END()
    return ret;
}
