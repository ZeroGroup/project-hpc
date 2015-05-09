#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setCentralWidget(new QLabel("Hello, World!"));
}

MainWindow::~MainWindow(){}

void MainWindow::createMenus() {}
void MainWindow::createStatusBar() {}
void MainWindow::createToolbars() {}
