#include "MainWindow.hpp"

#include <QDebug>

#include "SimulationData.hpp"

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    _sdata = NULL;

    setCentralWidget(_mdiArea = new QMdiArea());

    createActions();
    createMenus();
    createStatusBar();
    createToolbars();

    setMinimumSize(1280, 720);
    resize(1366, 768);
}

MainWindow::~MainWindow(){
}

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
    _fileSaveAsAct->setIcon(QIcon::fromTheme("document-save-as", QIcon(":/icons/save.png")));
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

    _fileSaveAct->setEnabled(false);
    _fileSaveAsAct->setEnabled(false);
    _fileCloseAct->setEnabled(false);
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
    auto fileToolBar = addToolBar(tr("Simulation"));
    fileToolBar->addAction(_fileNewAct);
    fileToolBar->addAction(_fileOpenAct);
    fileToolBar->addAction(_fileSaveAct);
    fileToolBar->addAction(_fileSaveAsAct);
}

#include <hpc/sensors/SensorNetwork.hpp>
#include "WorldWidget.hpp"

void MainWindow::fileNew() {
    if (_sdata)
        if (!_sdata->isSaved())
            maybeSave();
        fileClose();
    // if project exist,
        // if not saved,
            //maybe save?
        // close


    // run wizard
    QMdiSubWindow * world = _mdiArea->addSubWindow(new WorldWidget());
    world->setWindowTitle("*untitled");
    world->setMinimumSize(300, 200);
    world->show();

    _sdata = new SimulationData();
    _sdata->setSaved(false);

    connect(_sdata, SIGNAL(fileNameChanged(QString)), world, SLOT(setWindowTitle(QString)));

    SensorNetwork net(40);
    net.push();
    net.start();

    _fileSaveAsAct->setEnabled(true);
    _fileCloseAct->setEnabled(true);
}

void MainWindow::fileOpen() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::toNativeSeparators(QDir::homePath()),
                                                    tr("Simulation files (*.sim);;Text files (*.txt);;XML files (*.xml);;All files (*.*)"));

    if (_sdata)
        if (!_sdata->isSaved())
            maybeSave();
        fileClose();

    _sdata = new SimulationData();
    _sdata->setFileName(filename);
    _sdata->setSaved(true);

    SensorNetwork net;
    net.load(filename.toStdString());

    _fileSaveAsAct->setEnabled(true);
    _fileSaveAct->setEnabled(true);
    _fileCloseAct->setEnabled(true);
}

void MainWindow::fileSaveAs() {
    // QString filter = tr("Simulation files (*.sim);;Text files (*.txt);;XML files (*.xml);;All files (*.*)");

    QString filter = "Simulation files (*.sim)";
    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Save As..."),
                QDir::toNativeSeparators(QDir::homePath()),
                filter, &filter);

//    filename.append(".sim");

    if (filename.isEmpty()) {
//      filechooser canceled
        return;
    } else {
        _sdata->setFileName(filename);

        _fileSaveAct->setEnabled(true);
        fileSave();
    }
}

void MainWindow::fileSave() {
    if (_sdata->fileName().isEmpty()){
//      no file have been specified, call save as...
        return fileSaveAs();
    }

    SensorNetwork net(40);
    net.save(_sdata->fileName().toStdString());

    _sdata->setSaved(true);
}

void MainWindow::fileClose(){
    if (_sdata)
        delete _sdata;

    _sdata = NULL;

    _fileSaveAct->setEnabled(false);
    _fileSaveAsAct->setEnabled(false);
    _fileCloseAct->setEnabled(false);
}

void MainWindow::helpAbout(){
    QString aboutText = tr("The <b>HCP Project 2015</b> example demonstrates how to "
                           "write modern GUI applications using Qt, with a menu bar, "
                           "toolbars, and a status bar.");
    QString aboutTitle = tr("About HPC Project 2015");
    QMessageBox::about(this, aboutTitle, aboutText);
}

void MainWindow::helpAboutQt(){
    QString aboutQtTitle = tr("About Qt");
    QMessageBox::aboutQt(this, aboutQtTitle);
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

void MainWindow::maybeSave() {
    QMessageBox::StandardButton result = QMessageBox::question(this, "Unsaved changes", "Wanna save them?");
    if (QMessageBox::Yes == result) {
        fileSave();
    }
}
