#include <iostream>

#include "config.h"

#include <QtWidgets>

#include "MainWindow.hpp"

#include <hpc/sensors/SensorNetwork.hpp>

const QString app_name_format = "HPC Project v.%1";

using namespace std;

int main(int argc, char *argv[]){
    const QString app_name = app_name_format.arg(HPC_VERSION_STRING);

    cout << app_name.toStdString() << endl;

    QApplication app(argc, argv);

    QPixmap pixmap(":/img/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage(app_name);

    MainWindow window;
    window.show();

    splash.finish(&window);

    SensorNetwork sn(4);
    sn.start();

    return app.exec();
}
