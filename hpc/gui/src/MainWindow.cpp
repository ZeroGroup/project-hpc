#include "MainWindow.hpp"

#include <QDebug>

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setCentralWidget(_mdiArea = new QMdiArea());

    createActions();
    createMenus();
    createStatusBar();
    createToolbars();

    setMinimumSize(1280, 720);
    resize(1366, 768);
}

MainWindow::~MainWindow(){}

void MainWindow::createActions() {
    _fileNewAct = new QAction(tr("&New..."), this);
    _fileNewAct->setShortcut(QKeySequence::New);
    _fileNewAct->setStatusTip(tr("Create new simulation"));
    _fileNewAct->setIcon(QIcon::fromTheme("document-new", QIcon(":/icons/new.png")));
    connect(_fileNewAct, SIGNAL(triggered()), this, SLOT(fileNew()));


    _fileOpenAct = new QAction(tr("&Open..."), this);
    _fileOpenAct->setShortcut(QKeySequence::Open);
    _fileOpenAct->setStatusTip(tr("Load existing simulation data"));
    _fileOpenAct->setIcon(QIcon::fromTheme("document-open", QIcon(":/icons/open.png")));
    connect(_fileOpenAct, SIGNAL(triggered()), this, SLOT(fileOpen()));

    _fileCloseAct = new QAction(tr("&Close..."), this);
    _fileCloseAct->setShortcut(QKeySequence::Close);
    _fileCloseAct->setStatusTip(tr("Exit current simulation"));
    connect(_fileCloseAct, SIGNAL(triggered()), this, SLOT(fileClose()));

    _fileSaveAct = new QAction(tr("&Save"), this);
    _fileSaveAct->setShortcut(QKeySequence::Save);
    _fileSaveAct->setStatusTip(tr("Save simulation data to file"));
    _fileSaveAct->setIcon(QIcon::fromTheme("document-save", QIcon(":/icons/save.png")));
    connect(_fileSaveAct, SIGNAL(triggered()), this, SLOT(fileSave()));

    _fileSaveAsAct = new QAction(tr("Save &as..."), this);
    _fileSaveAsAct->setShortcut(QKeySequence::SaveAs);
    _fileSaveAsAct->setStatusTip(tr("Save simulation data to file"));
    _fileSaveAsAct->setIcon(QIcon::fromTheme("document-save-as"));
    connect(_fileSaveAsAct, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

    _fileExitAct = new QAction(tr("E&xit..."), this);
    _fileExitAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    _fileExitAct->setStatusTip(tr("Exit program"));
    _fileExitAct->setIcon(QIcon::fromTheme("application-exit"));
    connect(_fileExitAct, SIGNAL(triggered()), this, SLOT(close()));


    _helpAboutAct = new QAction(tr("&About"), this);
    _helpAboutAct->setStatusTip(tr("About HPC program"));
    _helpAboutAct->setIcon(QIcon::fromTheme("help-about"));
    connect(_helpAboutAct, SIGNAL(triggered()), this, SLOT(helpAbout()));

    _helpAboutQtAct = new QAction(tr("&About Qt"), this);
    _helpAboutQtAct->setStatusTip(tr("About Qt framework"));
    _helpAboutQtAct->setIcon(QIcon::fromTheme("help-about"));
    connect(_helpAboutQtAct, SIGNAL(triggered()), this, SLOT(helpAboutQt()));
}

void MainWindow::createMenus() {
    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(_fileNewAct);
    fileMenu->addAction(_fileOpenAct);
    fileMenu->addSeparator();
    fileMenu->addAction(_fileCloseAct);
    fileMenu->addSeparator();
    fileMenu->addAction(_fileSaveAct);
    fileMenu->addAction(_fileSaveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(_fileExitAct);

    QMenu * editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(tr("&Parameters..."));

    QMenu * helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(_helpAboutAct);
    helpMenu->addAction(_helpAboutQtAct);
}

void MainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Ready."), 5000);
}

void MainWindow::createToolbars() {
    auto fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(tr("&lol"));
}

#include <hpc/sensors/SensorNetwork.hpp>

void MainWindow::fileNew() {
    // run wizard
    QMdiSubWindow * world = _mdiArea->addSubWindow(new QLabel("The Real World"));
    world->setWindowTitle("World 1");
    world->setMinimumSize(300, 200);
    world->show();

    SensorNetwork net(40);
    net.push();
    net.start();
}

void MainWindow::fileOpen() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::toNativeSeparators(QDir::homePath()),
                                                    tr("Simulation files (*.sim);;Text files (*.txt);;XML files (*.xml);;All files (*.*)"));
//    QString filename = "file.nsim"; //! TODO: get filename from QFileCHooser dialog
    SensorNetwork net;
    net.load(filename.toStdString());
}

void MainWindow::fileClose(){

}

void MainWindow::fileSaveAs() {
    QString filter = tr("Simulation files (*.sim);;Text files (*.txt);;XML files (*.xml);;All files (*.*)");
//    QString filename = "file.nsim"; //! TODO: get filename from QFileCHooser dialog
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    QDir::toNativeSeparators(QDir::homePath()),
                                                    filter, &filter);

    qDebug() << qPrintable(filter);
    if (filename.isEmpty()) {
//      filechooser canceled
        return;
    } else {
        _filename = filename;
        fileSave();
    }
}

void MainWindow::fileSave() {
    if (!_filename.size()){
//      no file have been specified, call save as...
        return fileSaveAs();
    }

    SensorNetwork net(40);
    net.save(_filename.toStdString());
}

void MainWindow::helpAbout(){
    QString aboutText = tr("The <b>HCP Project 2015</b> example demonstrates how to "
                           "write modern GUI applications using Qt, with a menu bar, "
                           "toolbars, and a status bar.");
    QString aboutTitle = tr("About HPC Project 2015");
    QMessageBox::about(this, aboutTitle, aboutText);
}

void MainWindow::helpAboutQt(){

}

void MainWindow::closeEvent(QCloseEvent *event){
//    if (maybeSave()) {
//        writeSettings();
        event->accept();
//    } else {
//        event->ignore();
//    }
    qDebug() << "bye!";
}
