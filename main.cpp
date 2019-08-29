#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    static const char ENV_VAR_QT_DEVICE_PIXEL_RATIO[] = "QT_DEVICE_PIXEL_RATIO";
//    if (!qEnvironmentVariableIsSet(ENV_VAR_QT_DEVICE_PIXEL_RATIO)
//            && !qEnvironmentVariableIsSet("QT_AUTO_SCREEN_SCALE_FACTOR")
//            && !qEnvironmentVariableIsSet("QT_SCALE_FACTOR")
//            && !qEnvironmentVariableIsSet("QT_SCREEN_SCALE_FACTORS")) {
//        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    }

    return a.exec();
}
