#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QtWidgets>

class SimulationData;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget * parent = NULL, Qt::WindowFlags flags = 0);
    virtual ~MainWindow();
private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void createToolbars();

    QAction * _fileNewAct;
    QAction * _fileOpenAct;
    QAction * _fileCloseAct;
    QAction * _fileSaveAsAct;
    QAction * _fileSaveAct;
    QAction * _fileExitAct;

    QAction * _helpAboutAct;
    QAction * _helpAboutQtAct;

    QMdiArea * _mdiArea;

    SimulationData * _sdata;

private slots:
    void fileNew();
    void fileOpen();
    void fileClose();
    void fileSaveAs();
    void fileSave();

    void helpAbout();
    void helpAboutQt();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void maybeSave();
};

void test_network();

#endif	// MAIN_WINDOW_HPP_
