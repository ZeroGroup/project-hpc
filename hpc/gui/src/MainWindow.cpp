#include "MainWindow.hpp"

// #include <QMdiArea>

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setCentralWidget(_mdiArea = new QMdiArea());

    createActions();
    createMenus();
    createStatusBar();
    createToolbars();

    setMinimumSize(320, 240);
    resize(640, 480);
}

MainWindow::~MainWindow(){}

void MainWindow::createActions() {
    _newSim = new QAction(tr("&New..."), this);
    _newSim->setShortcut(QKeySequence::New);
    _newSim->setStatusTip(tr("Create new simulation"));
    connect(_newSim, SIGNAL(triggered()), this, SLOT(newSimulation()));

    _openSim = new QAction(tr("&Open..."), this);
    _openSim->setShortcut(QKeySequence::Open);
    _openSim->setStatusTip(tr("Open existing simulation"));
    connect(_openSim, SIGNAL(triggered()), this, SLOT(openSimulation()));

    _aboutAct = new QAction(tr("&About"), this);
    _aboutAct->setStatusTip(tr("About HPC program"));
    connect(_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    _aboutQtAct = new QAction(tr("&About Qt"), this);
    _aboutQtAct->setStatusTip(tr("About Qt framework"));
    connect(_aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(_newSim);
    fileMenu->addAction(_openSim);

    QMenu * editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(tr("&Parameters..."));

    QMenu * helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(_aboutAct);
    helpMenu->addAction(_aboutQtAct);
}

void MainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Ready."), 5000);
}

void MainWindow::createToolbars() {
    auto fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(tr("&lol"));
}

void MainWindow::newSimulation() {

}

void MainWindow::openSimulation() {

}

void MainWindow::about(){

}

void MainWindow::aboutQt(){

}
