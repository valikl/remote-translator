#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Utils/BB_Exception.h"
#include "BB_TTRTS/configmanager.h"
#include "BB_TTRTS/controller.h"
#define CONTROLLER (Controller::Instance())

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    
private:
    Ui::MainWindow *ui;
    void initController();
};

#endif // MAINWINDOW_H
