#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QtWidgets>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget * parent = NULL, Qt::WindowFlags flags = 0);
    virtual ~MainWindow();
private:
    void createMenus();
    void createStatusBar();
    void createToolbars();
};

void test_network();

#endif	// MAIN_WINDOW_HPP_
