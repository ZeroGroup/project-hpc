#include <iostream>

#include <QtWidgets>

#include <hpc/gui/MainWindow.hpp>

using namespace std;

int main(int ac, char *av[]){
    QApplication app(ac, av);

    test_network();

    QMainWindow * window = new QMainWindow();
    window->setCentralWidget(new QLabel("Hello, World!"));
    window->show();

    return app.exec();
}
