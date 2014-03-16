#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){

TRY_FUNC_WITH_RETURN(ConfigManager::Instance().init(false));

TRY_FUNC_WITH_RETURN(initController());

}

void MainWindow::initController()
{
    try
    {
        CONTROLLER.init();
    }
    catch(BB_Exception excp)
    {
        QMessageBox::critical(this, "Error:", QString::fromStdWString(excp.GetInfo()));
    }
}
