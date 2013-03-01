#include "broadcastcontroller.h"
#include "ui_broadcastcontroller.h"

BroadcastController::BroadcastController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BroadcastController)
{
    ui->setupUi(this);
}

BroadcastController::~BroadcastController()
{
    delete ui;
}
