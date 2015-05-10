#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QtWidgets>

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

    QAction * _newSim;
    QAction * _openSim;

    QAction * _aboutAct;
    QAction * _aboutQtAct;

    QMdiArea * _mdiArea;

private slots:
    void newSimulation();
    void openSimulation();

    void about();
    void aboutQt();
};

void test_network();

#endif	// MAIN_WINDOW_HPP_
